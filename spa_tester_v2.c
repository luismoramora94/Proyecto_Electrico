/////////////////////////////////////////////
//          SPA TESTER for SPA.C           //
//                                         //
//      Solar Position Algorithm (SPA)     //
//                   for                   //
//        Solar Radiation Application      //
//                                         //
//             August 12, 2004             //
//                                         //
//   Filename: SPA_TESTER.C                //
//                                         //
//   Afshin Michael Andreas                //
//   afshin_andreas@nrel.gov (303)384-6383 //
//                                         //
//   Measurement & Instrumentation Team    //
//   Solar Radiation Research Laboratory   //
//   National Renewable Energy Laboratory  //
//   1617 Cole Blvd, Golden, CO 80401      //
/////////////////////////////////////////////

/////////////////////////////////////////////
// This sample program shows how to use    //
//    the SPA.C code.                      //
/////////////////////////////////////////////

/////////////////////////////////////////////
// Modificado por Luis Fernando Mora para  //
// generar una herramienta en el diseño de //
// radiotelescopios de aplicación solar    //
// 			lmoramora94@gmail.com 		   //
/////////////////////////////////////////////

#include <stdio.h>
#include <math.h>
#include "spa.h"  //include the SPA header file

int main (int argc, char *argv[])
{
    spa_data spa;  //declare the SPA structure

    int result; // Variable de chequeo

	// Variables de Iteracion Y fechas de las velocidades maximas/minimas
	int year_i, mes_i, dia_i, hora_i, min_i, seg_i;
	int year_azimut_max, mes_azimut_max, dia_azimut_max, hora_azimut_max, min_azimut_max, seg_azimut_max;
	int year_altitud_max, mes_altitud_max, dia_altitud_max, hora_altitud_max, min_altitud_max, seg_altitud_max;
	int year_azimut_min, mes_azimut_min, dia_azimut_min, hora_azimut_min, min_azimut_min, seg_azimut_min;
	int year_altitud_min, mes_altitud_min, dia_altitud_min, hora_altitud_min, min_altitud_min, seg_altitud_min;

	// Variables temporales
	float temp_altitud_sol, temp_azimut_sol, v_altitud, v_azimut;

	// Inicializacion de velocidades maximas y minimas

	float v_azimut_min = 100;
	float v_altitud_min = 100;
	float v_altitud_max = 0;
	float v_azimut_max = 0;

    spa.year          = 2017;

	// Fijos para la antena

    spa.timezone      = -6.0; // -6 para Costa Rica UTC 6
    spa.delta_ut1     = 0; // WTF
    spa.delta_t       = 67; // Who knows
    spa.longitude     = -85.59611; // -85.5961111111111 antena en santa cruz
    spa.latitude      = 5; // 10.283333333333333 antena en santa cruz
    spa.elevation     = 3; // 3 msnm Santa Cruz
    spa.pressure      = 995; // 995 hPa o millibares (Valor promedio en Liberia)
    spa.temperature   = 28; // 28 C temperatura media para Santa Cruz
    spa.slope         = 0; // 0 si la base de concreto está nivelada
    spa.azm_rotation  = 0; // 0 si mido el azimut desde el sur, termino cte no afecta la velocidad
    spa.atmos_refract = 0.01; // Valor tipico
    spa.function      = SPA_ALL;


//for(mes_i = 1; mes_i<13; mes_i++){ // Iterar de enero a diciembre
//	spa.month         = mes_i;
	spa.month         = 1;
//	for(dia_i = 1; dia_i<31; dia_i++){ // Iterar del Dia 1 al dia 31
		spa.day = 1;
    	spa.hour          = 4;
    	spa.minute        = 59;
    	spa.second        = 59;

    	result = spa_calculate(&spa);
		temp_altitud_sol = spa.zenith;
		temp_azimut_sol = spa.azimuth;

		for(hora_i = 5; hora_i < 18; hora_i++){ // Iterar para 5:00 am a 5:59 pm
			for(min_i = 0; min_i < 60; min_i++){ // Iterar del minuto 0 al minuto 59
				for(seg_i = 0; seg_i<60; seg_i++){ // Iterar del segundo 0 al segundo 59

					spa.hour = hora_i;
					spa.minute = min_i;
					spa.second = seg_i;
    				spa_calculate(&spa);

					// Calculo de las Velocidades
					v_altitud = fabsf(spa.zenith - temp_altitud_sol); // Valor absoluto
					v_azimut = fabsf(spa.azimuth - temp_azimut_sol);

					// Actualizar los valores de la variable temporal

					temp_altitud_sol = spa.zenith;
					temp_azimut_sol = spa.azimuth;

					// Logica de seleccion de velocidades maximas y minimas

					if(v_altitud > v_altitud_max && v_altitud != 0){
						v_altitud_max    = v_altitud;
						year_altitud_max = spa.year;
						mes_altitud_max  = spa.month;
						dia_altitud_max  = spa.day;
						hora_altitud_max = spa.hour;
						min_altitud_max  = spa.minute;
						seg_altitud_max  = spa.second;
					};
					if(v_altitud < v_altitud_min && v_altitud != 0){
						v_altitud_min    = v_altitud;
						year_altitud_min = spa.year;
						mes_altitud_min  = spa.month;
						dia_altitud_min  = spa.day;
						hora_altitud_min = spa.hour;
						min_altitud_min  = spa.minute;
						seg_altitud_min  = spa.second;
					};
					if(v_azimut > v_azimut_max && v_altitud != 0){
						v_azimut_max     = v_azimut;
						year_azimut_max  = spa.year;
						mes_azimut_max  = spa.month;
						dia_azimut_max  = spa.day;
						hora_azimut_max = spa.hour;
						min_azimut_max  = spa.minute;
						seg_azimut_max  = spa.second;
					};
					if(v_azimut < v_azimut_min && v_altitud != 0){
						v_azimut_min = v_azimut;
						year_azimut_min = spa.year;
						mes_azimut_min  = spa.month;
						dia_azimut_min  = spa.day;
						hora_azimut_min = spa.hour;
						min_azimut_min  = spa.minute;
						seg_azimut_min  = spa.second;
					}
				}; // end for seg
			}; // end for min
		}; // end for hora
//	}; // end for dia
//}; // end for mes

    if (result == 0)  //check for SPA errors
    {
		printf("************************************************************************** \n");
		printf("Velocidad Azimuth Min:       	%.10f grados/s\n", v_azimut_min);
		printf("Año, mes, dia, hora, minuto, seg:       %d,%d,%d,%d,%d,%d\n", year_azimut_min, mes_azimut_min, dia_azimut_min, hora_azimut_min, min_azimut_min, seg_azimut_min);
		printf("----------------------------------------------------------------------- \n");
		printf("Velocidad Azimuth Max:       	%.10f grados/s\n", v_azimut_max);
		printf("Año, mes, dia, hora, minuto, seg:       %d,%d,%d,%d,%d,%d\n", year_azimut_max, mes_azimut_max, dia_azimut_max, hora_azimut_max, min_azimut_max, seg_azimut_max);
		printf("----------------------------------------------------------------------- \n");
		printf("Velocidad Altitud Min:       	%.10f grados/s\n", v_altitud_min);
		printf("Año, mes, dia, hora, minuto, seg:       %d,%d,%d,%d,%d,%d\n", year_altitud_min, mes_altitud_min, dia_altitud_min, hora_altitud_min, min_altitud_min, seg_altitud_min);
		printf("----------------------------------------------------------------------- \n");
		printf("Velocidad Altitud Max:       	%.10f grados/s\n", v_altitud_max);
		printf("Año, mes, dia, hora, minuto, seg:       %d,%d,%d,%d,%d,%d\n", year_altitud_max, mes_altitud_max, dia_altitud_max, hora_altitud_max, min_altitud_max, seg_altitud_max);
		printf("************************************************************************** \n");
    } else printf("SPA Error Code: %d\n", result);

    return 0;
}
