use anyhow::{Result, bail};
use opencv::{
    calib3d,
    core::{Mat, Point2f, Point3f, Size, Vector},
    imgproc,
    prelude::*,
};
use opencv::core::TermCriteria_Type;

use pipe_core::context::CameraCalibration;

pub fn calibrate_camera(
    images: Vec<Mat>,
    board_size: Size,
    square_size_mm: f32,
) -> Result<CameraCalibration> {

    if images.len() < 5 {
        bail!("Need at least 5 images for calibration");
    }

    // -------------------------------------------------
    // Prepare object points (3D, Z=0 plane)
    // -------------------------------------------------
    let mut objp = Vector::<Point3f>::new();
    for y in 0..board_size.height {
        for x in 0..board_size.width {
            objp.push(Point3f::new(
                x as f32 * square_size_mm,
                y as f32 * square_size_mm,
                0.0,
            ));
        }
    }

    let mut object_points = Vector::<Vector<Point3f>>::new();
    let mut image_points = Vector::<Vector<Point2f>>::new();

    let image_size = images[0].size()?;

    // -------------------------------------------------
    // Detect corners on RAW images only
    // -------------------------------------------------
    for img in &images {
        if img.size()? != image_size {
            bail!("All calibration images must have same resolution");
        }

        let mut gray = Mat::default();
        imgproc::cvt_color(
            img,
            &mut gray,
            imgproc::COLOR_BGR2GRAY,
            0,
            opencv::core::AlgorithmHint::ALGO_HINT_DEFAULT,
        )?;

        let mut corners = Vector::<Point2f>::new();
        let found = calib3d::find_chessboard_corners(
            &gray,
            board_size,
            &mut corners,
            calib3d::CALIB_CB_ADAPTIVE_THRESH
                | calib3d::CALIB_CB_NORMALIZE_IMAGE
                | calib3d::CALIB_CB_FAST_CHECK,
        )?;

        if !found {
            continue;
        }

        imgproc::corner_sub_pix(
            &gray,
            &mut corners,
            Size::new(11, 11),
            Size::new(-1, -1),
            opencv::core::TermCriteria::new(
                (TermCriteria_Type::COUNT as i32)
                    | (TermCriteria_Type::EPS as i32),
                30,
                0.001,
            )?,
        )?;

        image_points.push(corners);
        object_points.push(objp.clone());
    }

    // -------------------------------------------------
    // Safety check
    // -------------------------------------------------
    if image_points.len() < 5 {
        bail!(
            "Calibration failed: only {} valid frames detected",
            image_points.len()
        );
    }

    // -------------------------------------------------
    // Run calibration
    // -------------------------------------------------
    let mut camera_matrix = Mat::eye(3, 3, opencv::core::CV_64F)?.to_mat()?;
    let mut dist_coeffs = Mat::zeros(8, 1, opencv::core::CV_64F)?.to_mat()?;
    let mut rvecs = Vector::<Mat>::new();
    let mut tvecs = Vector::<Mat>::new();

    calib3d::calibrate_camera(
        &object_points,
        &image_points,
        image_size,
        &mut camera_matrix,
        &mut dist_coeffs,
        &mut rvecs,
        &mut tvecs,
        0,
        opencv::core::TermCriteria::default()?,
    )?;

    Ok(CameraCalibration {
        camera_matrix,
        dist_coeffs,
        px_to_mm: square_size_mm, // placeholder for now
    })
}
