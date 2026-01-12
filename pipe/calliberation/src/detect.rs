use anyhow::Result;
use opencv::{
    calib3d,
    core::{Mat, Point2f, Size, Vector},
    imgproc,
};
use opencv::core::TermCriteria_Type;

pub fn detect_chessboard(
    frame: &Mat,
    board_size: Size,
) -> Result<Option<Vector<Point2f>>> {

    let mut gray = Mat::default();
    imgproc::cvt_color(
        frame,
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
            | calib3d::CALIB_CB_NORMALIZE_IMAGE,
    )?;

    if found {
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
        Ok(Some(corners))
    } else {
        Ok(None)
    }
}
