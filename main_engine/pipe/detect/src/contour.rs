use opencv::{
    core::{Mat, Point, Vector},
    imgproc,
    Result,
};

pub fn extract_contours(mask: &Mat) -> Result<Vector<Vector<Point>>> {
    let mut contours: Vector<Vector<Point>> = Vector::new();

    imgproc::find_contours(
        mask,
        &mut contours,
        imgproc::RETR_EXTERNAL,
        imgproc::CHAIN_APPROX_SIMPLE,
        Point::new(0, 0),
    )?;

    Ok(contours)
}
