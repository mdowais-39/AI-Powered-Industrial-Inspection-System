use opencv::{
    core::{Mat, Point, RotatedRect, Size, Vector},
    imgproc,
    Result,
};

pub fn detect_parts(frame: &Mat) -> Result<Vec<RotatedRect>> {
    let mut gray = Mat::default();
    imgproc::cvt_color_def(frame, &mut gray, imgproc::COLOR_BGR2GRAY)?;

    let mut blurred = Mat::default();
    imgproc::gaussian_blur_def(&gray, &mut blurred, Size::new(5, 5), 0.0)?;

    let mut edges = Mat::default();
    imgproc::canny(&blurred, &mut edges, 60.0, 120.0, 3, false)?;

    let kernel = imgproc::get_structuring_element(
        imgproc::MORPH_RECT,
        Size::new(3, 3),
        Point::new(-1, -1),
    )?;

    let mut closed = Mat::default();
    imgproc::morphology_ex(
        &edges,
        &mut closed,
        imgproc::MORPH_CLOSE,
        &kernel,
        Point::new(-1, -1),
        1,
        opencv::core::BORDER_DEFAULT,
        imgproc::morphology_default_border_value()?,
    )?;

    let mut contours = Vector::<Vector<Point>>::new();
    imgproc::find_contours(
        &closed,
        &mut contours,
        imgproc::RETR_EXTERNAL,
        imgproc::CHAIN_APPROX_SIMPLE,
        Point::new(0, 0),
    )?;

    let mut parts = Vec::new();
    for c in contours {
        if c.len() < 5 {
            continue;
        }
        let r = imgproc::min_area_rect(&c)?;
        parts.push(r);
    }

    Ok(parts)
}
