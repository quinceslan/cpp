## I. Pagos
Escriba un programa que permita registrar los pagos diarios que se realizan a los socios y mostrar reportes de un Complejo Deportivo, para lo cual se tiene los siguientes datos en la tabla:

    ....
    +----------+----------+    +----------+----------+----------+----------+
    |Cant. Hij.|Pago      |    |Tipo Socio|Cuota Men.|Pag. Aniv.|P. canchas|
    +----------+----------+    +----------+----------+----------+----------+
    |  1 - 2   |    30.00 |    |Vip       |    90.00 |   20 %   |     4.00 |
    |  3 - 4   |    50.00 |    |Regular   |   120.00 |   25 %   |     6.00 |
    |  5 - 6   |    70.00 |    |Nuevo     |   170.00 |   30 %   |     8.00 |
    +----------+----------+    |Vitalicio |    60.00 |    -     |     -    |
                               +----------+----------+----------+----------+
    ....
### Registrar:
1. Ingresar el nombre del socio.
2. Ingresar el tipo de socio ( A - Vip, R - Regular, N - Nuevo, V - Vitalicio).
3. Ingresar la edad del socio, la cual debe ser entre 1 a 110 años.
4. Ingresar la cantidad de hijos que tiene el socio.
5. Ingresar la forma de Pago (E - Efectivo, T - Tarjeta, D - Depósito).
6. Ingresar la cantidad  de canchas a usar al mes.
7. Se atenderá si hay disponibilidad, de lo contrario puede dejar de atender, atender sólo la cantidad que tenga en stock o actualizar el stock y atender la cantidad solicitada.
8. Mostrará los siguentes montos en pantalla:
* MontoPagar= Cuota+ PagoAniver* Cuota+ CantCancha* Precio+ PagoDeHijos
* MontoIgv= MontoPagar* 18%
* TotalMes= MontoPagar+ MontoIgv
### Reportar
1. La cantidad de Tipo de sosios Vitalicios
2. La cantidad de pagos en depósitos
3. La cantidad de hijos de socios con rangos entre 3 - 4.
4. El monto acumulado de ingresos al mes
5. El monto acumulado de registros de socios sin hijos
6. El monto promedio de registros de socios Vip con edad mayor a 50

## En este ejercicio aplicara el uso de la estructura de control repetitiva
Escriba un programa que permita registrar las distribuciones que se realizará por la venta de celulares a "n clientes" y al finalizar mostrará un reporte final.

Los datos a registrar serán: nombre del cliente, dirección, tipo de celular (A - Alta gama, M - Media gama, B - Baja gama), tipo de pago (E - Efectivo, C - Crédito), tipo de cliente (E - Empresa, T - Tienda, B - Bodega), cantidad zona(A, B, C, D), el precio por tipo Celular: A - 4500, M - 3500, B - 2500

Por cada registro del cliente deberá mostrar el monto total: cantidad por precio y validar los datos ingresados.

Al finalizar todo el registro de "n clientes" debe mostrar lo siguiente:
* El número de registros de tipo celular B - Baja gama
* La cantidad de clientes registrados en Zona B
* La cantidad de tipo de datos en efectivo
* Monto acumulado de registros de tipo de cliente B
* El promedio acumulado de registros de tipo cliente - T y Zona - B
* El monto acumulado del registro de ventas
