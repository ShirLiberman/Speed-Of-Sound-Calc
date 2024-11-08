#include <iostream>
#include <cmath>
using namespace std;

void TotalPressureByHeight(double& Pressure_BY_Height, double SurfacePressure, double L_tempOfGrad, double height, double
 SurfaceTemperature, double G_gravity, double M_molar_mass_of_air, double R_constant_of_gasses, double expo)
{
    double temp = SurfacePressure * (1 - ((L_tempOfGrad * height) / SurfaceTemperature));
    double pow_res = (G_gravity * M_molar_mass_of_air) / (R_constant_of_gasses * L_tempOfGrad);
    Pressure_BY_Height = temp * pow(expo, pow_res);
}

void TempGrad(double& AirTemperature, double SurfaceTemperature, double height, double L_tempOfGrad)
{
    AirTemperature = SurfaceTemperature - ( height * L_tempOfGrad );
}

void Humidairbyheight(double& height_Humidity_Pv, double& Wet_molar, double Surface_Water_vapor_pressure, double height,
 double Mw, double G_gravity, double R_constant_of_gasses, double AirTemperature, double expo, double Pressure_BY_Height) 
{
    double arg = (((Mw * -1) * G_gravity * height) / (R_constant_of_gasses * AirTemperature));
    double power = pow(expo , arg);
    height_Humidity_Pv = Surface_Water_vapor_pressure * power;
    Wet_molar = height_Humidity_Pv / Pressure_BY_Height;
}

void TimeCalc(double& Sum_time, double AirTemperature, double Rd_constant_of_dry_air, double Rv_constant_of_water_vapor,
 double Specific_heat_ratio, double Wet_molar, double& C_Speed_Of_sound, double& dt)
{
    C_Speed_Of_sound = sqrt(Specific_heat_ratio * AirTemperature 
    * ((Rd_constant_of_dry_air * (1 - Wet_molar) + Rv_constant_of_water_vapor * Wet_molar)));
    dt = 1 / C_Speed_Of_sound; // update time increment
    Sum_time += dt; // accumulate time
}

int main() {
    double Sum_time = 0; 
    double dt = 1; 
    double height = 0; 
    double SurfacePressure = 0; 
    double G_gravity = 9.81; 
    double L_tempOfGrad = 0.0065; 
    double SurfaceTemperature = 0; 
    double AirTemperature = 0; 
    double R_constant_of_gasses = 8.31446; 
    double Rd_constant_of_dry_air = 287; 
    double Rv_constant_of_water_vapor = 461.5; 
    double M_molar_mass_of_air = 0.0289644; 
    double Pressure_BY_Height = 0; 
    double C_Speed_Of_sound = 0; 
    double Specific_heat_ratio = 1.4; 
    double height_Humidity_Pv = 0; 
    double relative_humidity_surface = 0; 
    double Surface_Water_vapor_pressure = 0; 
    double Surface_air_pressure = 101.325; 
    double expo = 2.71828;
    double Mw = 0.018016; 
    double Wet_molar = 0;

    cout << "Enter the height of object (meters): ";
    cin >> height;
    cout << "Enter the surface pressure (kPa): ";
    cin >> SurfacePressure;
    cout << "Enter the surface temperature (Celsius): ";
    cin >> SurfaceTemperature;
    SurfaceTemperature += 273.15; // from Celsius to Kelvin
    cout << "Enter the relative humidity in percent (%): ";
    cin >> relative_humidity_surface;

    Surface_Water_vapor_pressure = Surface_air_pressure * (relative_humidity_surface / 100.0);

    while(height > 0) 
    {
        TotalPressureByHeight(Pressure_BY_Height, SurfacePressure, L_tempOfGrad, height, SurfaceTemperature, G_gravity, M_molar_mass_of_air, R_constant_of_gasses, expo);
        TempGrad(AirTemperature, SurfaceTemperature, height, L_tempOfGrad);
        Humidairbyheight(height_Humidity_Pv, Wet_molar, Surface_Water_vapor_pressure, height, Mw, G_gravity, R_constant_of_gasses, AirTemperature, expo, Pressure_BY_Height);
        TimeCalc(Sum_time, AirTemperature, Rd_constant_of_dry_air, Rv_constant_of_water_vapor, Specific_heat_ratio, Wet_molar, C_Speed_Of_sound, dt);
        height -= dt * C_Speed_Of_sound; // update height based on time step and speed of sound
    }

    cout << "Estimated time to hear the explosion in air is: " << Sum_time << " seconds" << endl;
    return 0;
}
