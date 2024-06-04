#include <bits/stdc++.h>
using namespace std;
double randomDouble()
{

    int t = rand();
    return (double)(t % 100) / (double)(102);
}
vector<double> Surface_data(int u)
{
    switch (u)
    {
    case 1:
    {
        return {9.54, 13.95, 2.68, 0.254, 1250, 0.840};
    }
    case 2:
    {
        return {6.48, 16.00, 1.86, 0.152, 1804, 0.845};
    }
    case 3:
    {
        return {5.21, 19.82, 1.54, 0.102, 2231, 0.841};
    }
    case 4:
    {
        return {5.11, 20.06, 1.49, 0.102, 2290, 0.843};
    }
    default:
    {
        // Handle invalid input
        cout << "Invalid input for u\n";
        return {};
    }
    }
}

// Function to calculate alpha (heat transfer density from one side)

double alpha(double B1, double B2, double beta, double a = 0.1524)
{
    double cal = B1 + B2 + 2 * a;
    double ans = B1 / cal;
    return (ans * beta);
}

// Surface area of fluid flow
// double Surface_area(double width, double height, double length, double alpha)
// {
//     return width * alpha * height * length;
// }

// ratio of free flow area and frontal area

double Sigma(double alpha, double hydraulic_dia)
{
    return (hydraulic_dia * alpha) / (4 * 1000);
}

// Reynold number

double Reynold_no(double mass, double actual_area, double hydraulic_dia, double d_viscosity)
{
    // cout<<"G = "<<mass/actual_area<<endl;
    return (hydraulic_dia * mass * 10) / (actual_area * d_viscosity);
}

// prandtl number calculation

double prandtl_no(double d_viscosity, double specific_heat, double conductivity)
{
    return (d_viscosity * specific_heat) / (conductivity * 10000);
}

// heat transfer coefficient

double heat_transfer_coef(double colburn_fact, double mass, double actual_area, double specific_heat, double prandtl_no)
{
    double cal = pow(prandtl_no, 2.0 / 3.0);
    return (colburn_fact * specific_heat * mass) / (actual_area * cal);
}

// fin efficiency

double fin_eff(double heat_transfer_coeff, double metal_conduct, double thickness)
{
    double cal = (2.0 * heat_transfer_coeff * 1000) / (metal_conduct * thickness);
    cal = pow(cal, 0.5);
    return cal;
}
// net fin efficiency

double net_Fin_efficiency(double fin_eff, double fin_length)
{
    double u = 2 * fin_eff * fin_length;
    double o = exp(u);
    return (o - 1) / ((o + 1) * (u / 2));
}

// overall efficiency for a particular liquid

double overall_fluid_eff(double net_fin_eff, double surface_ratio)
{
    double cal = (1 - net_fin_eff);
    cal *= surface_ratio;
    return (1 - cal);
}
// overall heat transfer coefficient
double Overall_heat_tc(double overall_eff_c, double surface_area_c, double heat_transfer_coef_c, double overall_eff_h, double surface_area_h, double heat_transfer_coef_h)
{
    double cal = (1 / (overall_eff_c * surface_area_c * heat_transfer_coef_c));
    cal += (1 / (overall_eff_h * surface_area_h * heat_transfer_coef_h));
    return (1 / (surface_area_c * cal));
}

// Calculating NTU
double N_T_U(double overall_eff, double surface_area, double min_specific_heat, double mass)
{
    return (overall_eff * surface_area) / (min_specific_heat * mass);
}

// pressure functions

// entrance loss
double loss_1(double Kc, double sigma)
{
    return 1 + Kc - sigma * sigma;
}
// acceleration loss
double loss_2(double volume_out, double volume_in)
{
    return 2 * ((volume_out / volume_in) - 1);
}

// flow friction loss

double loss_3(double friction_fact, double surface_area, double actual_area, double volume_out, double volume_in)
{
    return friction_fact * surface_area * ((volume_out / volume_in) + 1) / (2 * actual_area);
}

// exit loss

double loss_4(double ke, double sigma, double volume_out, double volume_in)
{
    return (1 - sigma * sigma - ke) * volume_out / volume_in;
}

int main()
{

    srand(time(0));
    ofstream myfile("example.txt");
    for (int i1 = 0; i1 < 10000; i1++)
    {
        double Temp_c_in, Temp_h_in, Temp_c_out, Temp_h_out, mass_c, mass_h, specific_heat_c, specific_heat_h, d_viscos_h, d_viscos_c, conduct_c, conduct_h;

        double i1_rand = randomDouble();
        Temp_c_in = 50 + (20) * i1_rand;
        // cout << "Enter the mass flow rate of Cold fluid (in Kg/s): ";
        double i10_rand = randomDouble();
        mass_c = 0.5 + 0.1 * i10_rand;
        specific_heat_c = 1054;
        d_viscos_c = 0.00002277;
        conduct_c = 0.028;
        // cout << "\nEnter the details of Hot fluid :" << endl;
        // cout << "Enter the Hot fluid inlet Temperature (in *C): ";

        double i2_rand = randomDouble();
        Temp_h_in = 300 + 120 * i2_rand;
        // cout << "Exit temperature of hot fluid required (in *C): ";
        double Heat;

        double i3_rand = randomDouble();
        Heat = 100 + 50 * i3_rand;
        // cout << "Enter the mass flow rate of Hot fluid (in Kg/s): ";
        double i9_rand = randomDouble();
        mass_h = 0.5 + 0.1 * i9_rand;
        specific_heat_h = 1071.1;
        d_viscos_h = 0.0000264;
        conduct_h = 0.0341;

        Temp_h_out = Temp_h_in - (Heat * 1000.0) / (mass_h * specific_heat_h);
        Temp_c_out = Temp_c_in + (Heat * 1000 / (mass_c * specific_heat_c));
        // cout<<"Heat : "<<Heat<<" "<<Temp_c_out<<endl;

        double height, depth, width, volume, total_surface_area_c, total_surface_area_h;

        double i4_rand = randomDouble();
        volume = 0.006 + 0.004 * i4_rand;
        height = 0.2518;
        double random = randomDouble();
        depth = (0.5 + 1.5 * random) * (volume / height);
        width = volume / (depth * height);

        double Cr = (specific_heat_c * mass_c) / (specific_heat_h * mass_h);
        // cout<<"Heat : "<<Heat<<" "<<Temp_c_out<<endl;
        // cout << "\nWhat type of Surface type is used for Hot fluid \n";

        // double height, depth, width, volume, total_surface_area_c, total_surface_area_h;
        for (int i7 = 1; i7 <= 4; i7++)
        {
            vector<double> surface_data_c = Surface_data(i7);
            for (int i8 = 1; i8 < 5; i8++)
            {
                vector<double> surface_data_h = Surface_data(i8);
                double prandtl_no_c = prandtl_no(d_viscos_c, specific_heat_c, conduct_c);
                double prandtl_no_h = prandtl_no(d_viscos_h, specific_heat_h, conduct_h);
                double frontal_area_c, frontal_area_h;

                // considering frontal area of cold fluid as width cross
                frontal_area_c = width * height;
                frontal_area_h = depth * height;

                double alpha_c = alpha(surface_data_c[0], surface_data_h[0], surface_data_c[4]);
                double alpha_h = alpha(surface_data_h[0], surface_data_c[0], surface_data_h[4]);
                total_surface_area_c = alpha_c * volume;
                total_surface_area_h = alpha_h * volume;
                double sigma_c = Sigma(alpha_c, surface_data_c[2]);
                double sigma_h = Sigma(alpha_h, surface_data_h[2]);
                double actual_area_c = frontal_area_c * sigma_c;
                double actual_area_h = frontal_area_h * sigma_h;
                double reynold_no_c = Reynold_no(mass_c, actual_area_c, surface_data_c[2], d_viscos_c);
                double reynold_no_h = Reynold_no(mass_h, actual_area_h, surface_data_h[2], d_viscos_h);

                double j_factor_c = 0.47 / pow(reynold_no_c, 0.5);
                double j_factor_h = 0.47 / pow(reynold_no_h, 0.5);

                // characteristics values for both fluids and friction factors
                double kec, kc, keh, kh, fc, fh;
                if (reynold_no_c > 2000)
                {
                    kc = 0.6 - 0.45 * sigma_c;
                    kec = 1 - 1.15 * sigma_c;
                    fc = 0.26 / pow(reynold_no_c, 0.25);
                }
                else
                {
                    kc = 1.3 - 0.35 * sigma_c;
                    kec = 1 - 1.9 * sigma_c;
                    fc = 0.43 / pow(reynold_no_c, 0.3);
                }
                if (reynold_no_h > 2000)
                {
                    kh = 0.6 - 0.45 * sigma_h;
                    keh = 1 - 1.15 * sigma_h;
                    fh = 0.26 / pow(reynold_no_h, 0.25);
                }
                else
                {
                    kh = 1.3 - 0.35 * sigma_h;
                    keh = 1 - 1.9 * sigma_h;
                    fh = 0.43 / pow(reynold_no_h, 0.3);
                }

                double h_t_c = heat_transfer_coef(j_factor_c, mass_c, actual_area_c, specific_heat_c, prandtl_no_c);
                double h_t_h = heat_transfer_coef(j_factor_h, mass_h, actual_area_h, specific_heat_h, prandtl_no_h);
                double metal_conduct = 202.3;
                // cout << "Enter the value of the conductivity of metal used in Heat Exchanger (W/mk) : ";
                // metal_conduct;
                double fin_eff_c = fin_eff(h_t_c, metal_conduct, surface_data_c[3]);
                double fin_eff_h = fin_eff(h_t_h, metal_conduct, surface_data_h[3]);

                double leng_fin = 3.175 / 1000.0;

                double net_fin_eff_c = net_Fin_efficiency(fin_eff_c, leng_fin);
                double overall_fluid_eff_c = overall_fluid_eff(net_fin_eff_c, surface_data_c[5]);
                double net_fin_eff_h = net_Fin_efficiency(fin_eff_h, leng_fin);
                double overall_fluid_eff_h = overall_fluid_eff(net_fin_eff_h, surface_data_h[5]);

                double overall_heat_coef, NTU, effectiveness;
                if (mass_c * specific_heat_c > mass_h * specific_heat_h)
                {
                    overall_heat_coef = Overall_heat_tc(overall_fluid_eff_h, total_surface_area_h, h_t_h, overall_fluid_eff_c, total_surface_area_c, h_t_c);
                    NTU = N_T_U(overall_heat_coef, total_surface_area_h, specific_heat_h, mass_h);
                    effectiveness = (Temp_h_in - Temp_h_out) / (Temp_h_in - Temp_c_in);
                }
                else
                {
                    overall_heat_coef = Overall_heat_tc(overall_fluid_eff_c, total_surface_area_c, h_t_c, overall_fluid_eff_h, total_surface_area_h, h_t_h);
                    NTU = N_T_U(overall_heat_coef, total_surface_area_c, specific_heat_c, mass_c);
                    effectiveness = (Temp_c_out - Temp_c_in) / (Temp_h_in - Temp_c_in);
                }

                // cout<<"\nOverall_heat_coef : "<<overall_heat_coef<<endl;
                double press_in_c, press_in_h, press_out_c, press_out_h, press_drop_all_c, press_drop_all_h;

                // cout << "\nEnter the pressure of the cold fluid at inlet (in Kpa): ";

                press_in_c = 55;
                // cout << "Enter the allowed pressure drop for cold fluid flow (in Kpa): ";
                press_drop_all_c = 20;
                press_out_c = press_in_c - press_drop_all_c;
                double input_vol_c, output_vol_c;
                input_vol_c = (287 * (Temp_c_in + 273)) / (press_in_c * 1000);
                output_vol_c = (287 * (Temp_c_out + 273)) / (press_out_c * 1000);

                // Cold fluid pressure
                double cal = loss_1(kc, sigma_c) + loss_2(output_vol_c, input_vol_c) + loss_3(fc, total_surface_area_c, actual_area_c, output_vol_c, input_vol_c) - loss_4(kec, sigma_c, output_vol_c, input_vol_c);
                double press_loss_c = (mass_c * mass_c) / (actual_area_c * actual_area_c);
                press_loss_c *= input_vol_c / (2 * 9.80665);
                press_loss_c *= cal;
                press_loss_c /= 1000;

                // hot fluid pressure
                // cout << "\nEnter the pressure of the cold fluid at inlet (in Kpa): ";

                press_in_h = 380;
                // cout << "Enter the allowed pressure drop for cold fluid flow (in Kpa): ";
                press_drop_all_h = 10;
                press_out_h = press_in_h - press_drop_all_h;
                double input_vol_h, output_vol_h;
                input_vol_h = (287 * (Temp_h_in + 273)) / (press_in_h * 1000);
                output_vol_h = (287 * (Temp_h_out + 273)) / (press_out_h * 1000);

                double cal2 = loss_1(kh, sigma_h) + loss_2(output_vol_h, input_vol_h) + loss_3(fh, total_surface_area_h, actual_area_h, output_vol_h, input_vol_h) - loss_4(keh, sigma_h, output_vol_h, input_vol_h);
                double press_loss_h = (mass_h * mass_h) / (actual_area_h * actual_area_h);

                // correlation for effectiveness and NTU in cross flow heat exchanger
                press_loss_h *= input_vol_h / (2 * 9.80665);
                press_loss_h /= 1000;
                press_loss_h *= cal2;
                double cal4 = pow(NTU, 0.78);
                double cal5 = NTU / cal4;
                cal4 *= Cr;
                cal4 = exp(-1.0 * cal4);
                cal4 -= 1;
                cal5 *= cal4 / Cr;
                cal5 = exp(cal5);
                double eff = 1 - cal5;
                Temp_h_out = Temp_h_in - eff * Cr * (Temp_h_in - Temp_c_in);
                Temp_c_out = eff * (Temp_h_in - Temp_c_in) + Temp_c_in;
                // cout<<eff<<" ";
                // i7, i8 represent the surfce types used in strip fins
                if (Temp_c_in <= Temp_h_out && Temp_c_out <= Temp_h_in)
                    myfile << i7 << " " << i8 << " " << mass_c << " " << mass_h << " " << Temp_c_in << " " << Temp_h_in << " " << Heat << " " << height << " " << depth << " " << width << " " << Temp_h_out << " " << Temp_c_out << " " << eff << " " << press_loss_c << " " << press_loss_h << endl;
                // cout << "NTU of system : " << NTU << endl;
                // cout << "Overall Heat transfer coefficient of the system is (in W/m²k)" if (press_loss_c > press_drop_all_c)
                // {
                //     cout << "Our Heat Exchanger is not capable of functioning with cold fluid pressure drop\n";
                // }
                // if (press_loss_h > press_drop_all_h)
                // {
                //     cout << "Our Heat Exchanger is not capable of functioning with Hot fluid pressure drop\n";
                // }
            }
        }
    }
    myfile.close();
    return 0;
}
