void loop() {
    on_or_off = timing(delay_input);
    angular_velocity = run_gyrometer();
    smooth_angular_velocity = smoother(angular_velocity);
    changeInAngle = ChangeInAngle(smooth_angular_velocity);
    accelarations = run_accelerometer();
    smooth_accelarations = smoother(accelarations);
    stroke_rate = strokeRate(smooth_accelarations);
}
