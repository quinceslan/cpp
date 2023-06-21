## Enunciado del problema
Se requiere un programa para la reserva de tiquetes aéreos de vuelo de avionetas que van desde la ciudad de Villavicencio hasta la Sierra de la Macarena:
* La avioneta tiene 10 filas (0, 9) y 5 puestos en cada fila.
* El valor del tiquete de la fila 0 a la 4 tiene un valor de $600000, dado que es categoría preferencial y de la fila 5 a la 9, cuesta $450000, dado que es categoría general.
* En la iagen se muestra una posible muestra de la venta de tiquetes:

Por ejemplo, La señora Juanita Acosta Yepes compro un tiquete en la primera silla de la fila 0.
Octavio Paz compro la silla 3 en la fila 5.

## Se require lo siguiente:
1. Registrar la venta de tiequetes, preguntando en la fila y en qué puesto desea comprar, para lo cual debe verificar si la silla que quiere comprar está libre. Si está libre se realiza el registro del nombre del pasajero y su numero de documento de identidad (como se observa en la imagen).
2. Conocer el valor recogido en la aerolínea por concepto de venta de tiquetes aéreos de la categoría preferencial y el valor recogido en la aerolínea por concepto de venta de tiquetes aéreos de la categoría general.
3. Dado el nombre de una persona, decir la ubicación de su silla, por ejemplo si tiene el nombre Octavio Paz se debe decir que compró la silla 3 de la fila 5.
4. Mostrar la información de todos los pasajeros en un solo mensaje de texto.
5. Listar en un vector todos los nombres y ordenarlos alfabeticamente.
6. Dado la ubicacion de la silla, mostrar la informacion del pasajero que compró el tiquete de esta silla.
7. Cancelar la compra de un tiquete, dada la cédula del pasajero.

....

    ---------------------------------------------------------------------
    |Juanito       |Consuleo     |Jair        |            |            |
    |Yepes         |Ramirez      |Velasco     |            |            |
    |12345678      |12345678     |123456788   |            |            |
    ---------------------------------------------------------------------
    |Javier        |             |            |            |Luis        |
    |Vasques       |             |            |            |Carvajal    |
    |12345678      |             |            |            |34902145    |
    ---------------------------------------------------------------------
    |Sara          |             |            |Francisco   |            |
    |Mazuera       |             |            |Cruz        |            |
    |123456789     |             |            |15678902    |            |
    ---------------------------------------------------------------------
....
