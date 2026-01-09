use opencv::core::RotatedRect;
use serde::Deserialize;

#[derive(Deserialize)]
pub struct Constraints {
    pub expected_count: usize,
    pub part_constraints: PartConstraints,
    pub spacing_constraints: SpacingConstraints,
}

#[derive(Deserialize)]
pub struct PartConstraints {
    pub min_width_px: f32,
    pub max_width_px: f32,
    pub min_height_px: f32,
    pub max_height_px: f32,
    pub min_aspect_ratio: f32,
    pub max_aspect_ratio: f32,
    pub max_rotation_deg: f32,
}

#[derive(Deserialize)]
pub struct SpacingConstraints {
    pub min_distance_px: f32,
    pub max_distance_px: f32,
}

/// Edge-to-edge distance approximation
fn edge_distance(a: &RotatedRect, b: &RotatedRect) -> f32 {
    let ca = a.center;
    let cb = b.center;

    let center_dist =
        ((ca.x - cb.x).powi(2) + (ca.y - cb.y).powi(2)).sqrt();

    let ra = a.size.width.max(a.size.height) / 2.0;
    let rb = b.size.width.max(b.size.height) / 2.0;

    center_dist - ra - rb
}

/// MAIN VALIDATION FUNCTION
pub fn validate(
    parts: &[RotatedRect],
    cfg: &Constraints,
    frame_size: (i32, i32),
) -> bool {
    // ---------- Count check ----------
    if parts.len() != cfg.expected_count {
        return false;
    }

    let frame_area = (frame_size.0 * frame_size.1) as f32;

    // ---------- Per-part validation ----------
    for p in parts {
        let w = p.size.width.min(p.size.height);
        let h = p.size.width.max(p.size.height);

        // --- AREA DOMINANCE REJECTION ---
        let part_area = p.size.width * p.size.height;
        let area_ratio = part_area / frame_area;

        // Reject carrier / base / background
        if area_ratio > 0.5 {
            return false;
        }

        // --- SIZE CHECK ---
        if w < cfg.part_constraints.min_width_px
            || w > cfg.part_constraints.max_width_px
            || h < cfg.part_constraints.min_height_px
            || h > cfg.part_constraints.max_height_px
        {
            return false;
        }

        // --- ASPECT RATIO ---
        let aspect = w / h;
        if aspect < cfg.part_constraints.min_aspect_ratio
            || aspect > cfg.part_constraints.max_aspect_ratio
        {
            return false;
        }

        // --- ROTATION ---
        if p.angle.abs() > cfg.part_constraints.max_rotation_deg {
            return false;
        }
    }

    // ---------- SPACING ----------
    for i in 0..parts.len() {
        for j in (i + 1)..parts.len() {
            let d = edge_distance(&parts[i], &parts[j]);
            if d < cfg.spacing_constraints.min_distance_px
                || d > cfg.spacing_constraints.max_distance_px
            {
                return false;
            }
        }
    }

    true
}
