
use anyhow::Result;
use opencv::{
    core::{Point, Point2f, Scalar, Vector},
    imgproc,
};
use pipe_core::{context::PipeContext, stage::Stage};
use serde::{Serialize, Deserialize};
use chrono::Utc;

#[derive(Debug, Serialize, Deserialize)]
struct PartMatchResult {
    part_id: usize,
    status: String,  // "matched", "skipped", "not_found"
    reference_area: f64,
    #[serde(skip_serializing_if = "Option::is_none")]
    matched_contour_id: Option<usize>,
    #[serde(skip_serializing_if = "Option::is_none")]
    live_area: Option<f64>,
    #[serde(skip_serializing_if = "Option::is_none")]
    match_score: Option<f64>,
    #[serde(skip_serializing_if = "Option::is_none")]
    confidence: Option<f64>,
    candidates_tested: usize,
}


#[derive(Debug, Serialize, Deserialize)]
struct ComparisonSummary {
    timestamp: String,
    module: String,
    event: String,
    data: ComparisonData,
}

#[derive(Debug, Serialize, Deserialize)]
struct ComparisonData {
    reference_contours: usize,
    live_contours: usize,
    total_parts: usize,
    found_parts: usize,
    parts: Vec<PartMatchResult>,
}

pub struct CompareStage {
    reference_contours: Vector<Vector<Point>>,
}

impl CompareStage {
    pub fn new(reference_contours: Vector<Vector<Point>>) -> Self {
        Self { reference_contours }
    }
}

impl Stage for CompareStage {
    fn name(&self) -> &'static str {
        "CompareStage"
    }

    fn run(&mut self, ctx: &mut PipeContext) -> Result<()> {
        let frame = match ctx.frame.as_mut() {
            Some(f) => f,
            None => return Ok(()),
        };

        let live_contours = &ctx.contours;
        
        println!("\n═══════════════════════════════════════════════════════════");
        println!("[COMPARE] Starting comparison");
        println!("[COMPARE] Reference contours: {}", self.reference_contours.len());
        println!("[COMPARE] Live contours: {}", live_contours.len());
        println!("═══════════════════════════════════════════════════════════");
        
        // Track which live contours have been matched
        let mut matched_live_indices = vec![false; live_contours.len()];
        let mut total_parts = self.reference_contours.len();
        let mut found_parts = 0;
        let mut parts: Vec<PartMatchResult> = Vec::new();  // Collect results for JSON

        // Iterate over reference contours and check if they exist in live contours
        for (i, ref_contour) in self.reference_contours.iter().enumerate() {
            let mut found = false;
            let mut best_match_idx = 0;
            let mut min_match_val = 1.0; // Lower is better for match_shapes
            
            let ref_area = imgproc::contour_area(&ref_contour, false)?;
            
            println!("\n--- Reference Part {} ---", i);
            println!("[PART {}] Area: {:.2} px²", i, ref_area);
            
            // Skip very small reference parts (noise from calibration)
            if ref_area < 2000.0 {
                total_parts -= 1;
                println!("[PART {}] ⚠ SKIPPED - Area too small (noise)", i);
                parts.push(PartMatchResult {
                    part_id: i,
                    status: "skipped".to_string(),
                    reference_area: ref_area,
                    matched_contour_id: None,
                    live_area: None,
                    match_score: None,
                    confidence: None,
                    candidates_tested: 0,
                });
                continue;
            }

            let mut candidates_tested = 0;
            for (j, live_contour) in live_contours.iter().enumerate() {
                if matched_live_indices[j] {
                    continue; // Already matched
                }
                
                let live_area = imgproc::contour_area(&live_contour, false)?;
                
                // Skip small contours (noise)
                if live_area < 2000.0 {
                    continue;
                }

                candidates_tested += 1;
                
                // Area-based filtering - improved threshold
                let area_ratio = if ref_area > live_area {
                    live_area / ref_area
                } else {
                    ref_area / live_area
                };

                println!("[PART {}] Candidate {}: Live area={:.2}, Ratio={:.3}", 
                         i, j, live_area, area_ratio);

                if area_ratio < 0.6 {
                    println!("[PART {}]   → REJECTED - Area ratio too low (< 0.6)", i);
                    continue; // Size mismatch
                }

                // Shape matching using Hu Moments
                let match_val = imgproc::match_shapes(
                    &ref_contour,
                    &live_contour,
                    imgproc::CONTOURS_MATCH_I1,
                    0.0,
                )?;

                println!("[PART {}]   → Match score: {:.6} (lower is better)", i, match_val);

                // Improved threshold - lower = better match
                if match_val < 0.15 { 
                     if match_val < min_match_val {
                         min_match_val = match_val;
                         best_match_idx = j;
                         found = true;
                         println!("[PART {}]   → ✓ NEW BEST MATCH (score: {:.6})", i, match_val);
                     } else {
                         println!("[PART {}]   → Good match but not best", i);
                     }
                } else {
                    println!("[PART {}]   → REJECTED - Match score too high (>= 0.15)", i);
                }
            }
            
            println!("[PART {}] Tested {} candidates", i, candidates_tested);
            
            if found {
                found_parts += 1;
                matched_live_indices[best_match_idx] = true;
                
                let live_area = imgproc::contour_area(&live_contours.get(best_match_idx)?, false)?;
                println!("[PART {}] ✅ MATCHED to live contour {} (score: {:.6}, confidence: {:.1}%)", 
                         i, best_match_idx, min_match_val, (1.0 - min_match_val) * 100.0);
                println!("[PART {}]   Ref area: {:.2}, Live area: {:.2}", i, ref_area, live_area);
                
                // Add to JSON results
                parts.push(PartMatchResult {
                    part_id: i,
                    status: "matched".to_string(),
                    reference_area: ref_area,
                    matched_contour_id: Some(best_match_idx),
                    live_area: Some(live_area),
                    match_score: Some(min_match_val),
                    confidence: Some((1.0 - min_match_val) * 100.0),
                    candidates_tested,
                });
                
                let live_contour = live_contours.get(best_match_idx)?;
                
                // Draw rotated rectangle (like pipe's OverlayStage)
                let min_rect = imgproc::min_area_rect(&live_contour)?;
                let mut pts2f = [Point2f::default(); 4];
                min_rect.points(&mut pts2f)?;
                
                // Draw the rotated rectangle
                for k in 0..4 {
                    let p1 = Point::new(pts2f[k].x as i32, pts2f[k].y as i32);
                    let p2 = Point::new(
                        pts2f[(k + 1) % 4].x as i32,
                        pts2f[(k + 1) % 4].y as i32,
                    );
                    
                    imgproc::line(
                        frame,
                        p1,
                        p2,
                        Scalar::new(0.0, 255.0, 0.0, 0.0), // Green
                        2,
                        imgproc::LINE_8,
                        0,
                    )?;
                }
                
                // Label with part number and match quality
                let center = min_rect.center;
                let label = format!("Part {} (≈{:.1}%)", i, (1.0 - min_match_val) * 100.0);
                
                imgproc::put_text(
                    frame,
                    &label,
                    Point::new(center.x as i32 - 40, center.y as i32 - 10),
                    imgproc::FONT_HERSHEY_SIMPLEX,
                    0.5,
                    Scalar::new(0.0, 255.0, 0.0, 0.0),
                    1,
                    imgproc::LINE_AA,
                    false,
                )?;
            } else {
                println!("[PART {}] ❌ NOT FOUND - No suitable match", i);
                
                // Add to JSON results
                parts.push(PartMatchResult {
                    part_id: i,
                    status: "not_found".to_string(),
                    reference_area: ref_area,
                    matched_contour_id: None,
                    live_area: None,
                    match_score: None,
                    confidence: None,
                    candidates_tested,
                });
                
                // Missing part - indicate on screen
                imgproc::put_text(
                    frame,
                    &format!("⚠ MISSING: Part {}", i),
                    Point::new(10, 150 + (i as i32 * 35)),
                    imgproc::FONT_HERSHEY_SIMPLEX,
                    0.7,
                    Scalar::new(0.0, 0.0, 255.0, 0.0), // Red
                    2,
                    imgproc::LINE_AA,
                    false,
                )?;
            }
        }
        
        println!("\n═══════════════════════════════════════════════════════════");
        println!("[COMPARE] SUMMARY: Found {}/{} parts", found_parts, total_parts);
        if found_parts == total_parts {
            println!("[COMPARE] ✅ ALL PARTS PRESENT");
        } else {
            println!("[COMPARE] ⚠ {} PARTS MISSING", total_parts - found_parts);
        }
        println!("═══════════════════════════════════════════════════════════\n");
        
        // Output JSON summary
        let summary = ComparisonSummary {
            timestamp: Utc::now().to_rfc3339(),
            module: "compare".to_string(),
            event: "comparison_complete".to_string(),
            data: ComparisonData {
                reference_contours: self.reference_contours.len(),
                live_contours: live_contours.len(),
                total_parts,
                found_parts,
                parts,
            },
        };
        
        // Keep this JSON on a single line so backend line-reader can forward it intact.
        if let Ok(json) = serde_json::to_string(&summary) {
            println!("JSON_OUTPUT:{}", json);
        }
        
        // Display summary
        let status_color = if found_parts == total_parts {
            Scalar::new(0.0, 255.0, 0.0, 0.0) // Green - all parts found
        } else {
            Scalar::new(0.0, 165.0, 255.0, 0.0) // Orange - parts missing
        };
        
        imgproc::put_text(
            frame,
            &format!("Parts: {}/{}", found_parts, total_parts),
            Point::new(10, 120),
            imgproc::FONT_HERSHEY_SIMPLEX,
            0.7,
            status_color,
            2,
            imgproc::LINE_AA,
            false,
        )?;

        Ok(())
    }
}
