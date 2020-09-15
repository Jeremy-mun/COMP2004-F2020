#include <stdio.h> 
/*
A function definition has this form:

return-type   function-name(parameter declarations, if any)
{
          declarations
          statements
}


*/

/* Function definition for celciustofahrenheit */
float celsiustofahrenheit(float celsius);

int main()
{
	float celsius;
	int lower, upper, step;
	
	lower = 0.0;	/* lower limit of temperature table */
	upper = 100.0;	/* upper limit */
	step = 10;	/* step size */

	celsius = lower;

	printf("Celsius-Fahrenheit table\n");
	while (celsius <= upper) {
		printf("%3.0f %6.1f\n", celsius, celsiustofahrenheit(celsius));
		celsius = celsius + step;
	}
}

float celsiustofahrenheit(float celsius)
{
	return (celsius * 9.0 / 5.0) + 32.0;
}
