#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
#include <time.h>
#include "pdfgen.h"

//Detalles de los productos en el catalogo
struct productos{    
    char marca[30];
    float precio;
    int stock;
    int necesidad;
    float iva;
};

//Funcion para ordenar el inventario de A a la Z usando Selection Sort
void ordenarInventarioA_Z(struct productos lista[], int tamanioArreglo){
    //Si strcmp devuelve un valor mayor a 0, el primer nombre va después en el abecedario que el segundo
    //Si devuelve 0 son iguales
    //Si strcmp devuelve un valor menor a 0, el primer nombre va antes
    for (int i = 0; i < tamanioArreglo - 1; i++){
        int min = i;    //Posición del valor que va antes
        for (int j = i+1; j < tamanioArreglo; j++){
            if(strcmp(lista[j].marca, lista[min].marca) < 0 ){
                min = j;
            }
        }
        if (min != i){
            //Intercambio toda la estructura del producto para ordenar precio, stock y demás
            struct productos temp = lista[i];
            lista[i] = lista[min];
            lista[min] = temp;
        }
    }
}

//Funcion para buscar elemento en la lista usando Binary Search
int buscarProducto(struct productos lista[], int tamanioArreglo, int i){
    char n[40];
    strcpy(n, lista[i].marca);

    int encontrado = 0;
    int inferior = 0;
    int superior = tamanioArreglo - 1;

    while (inferior <= superior && encontrado == 0){
        int mitad = (inferior + superior)/2;
        if(strcmp(lista[mitad].marca, n) == 0){
            encontrado = 1;
        } else if(strcmp(lista[mitad].marca, n) < 0){
            inferior = mitad + 1;
        } else{
            superior = mitad - 1;
        }   
    }
    return encontrado;  //Devuelve el valor de 1 si encontró el elemento
}

//Funcion para abrir la caja o mantenerla cerrada
//Encargada de dar paso a que funcione todo el programa
int abrirCaja(int estadoCaja) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int opcion;

    if (estadoCaja == 1) {
        SetConsoleTextAttribute(hConsole, 10); // Verde
        printf("\n");
        printf("*----------------------*\n");
        printf("|##   CAJA ABIERTA   ##|\n");
        printf("*----------------------*\n");
        SetConsoleTextAttribute(hConsole, 7);  // Color por defecto
        return 1;
    }

    //Si estadoCaja == 0 pues la caja inicialmente esta cerrada
    printf("\n");
    SetConsoleTextAttribute(hConsole, 12); // Rojo
    printf("*----------------------*\n");
    printf("|##   CAJA CERRADA   ##|\n");
    printf("*----------------------*\n");
    SetConsoleTextAttribute(hConsole, 7);  // Color por defecto
    printf("*----------------------------------------------------------------------*\n");
    printf("|##   Digite 1 para abrirla y empezar el turno (0 para cancelar):    ##|\n");
    printf("*----------------------------------------------------------------------*\n");
    printf(">>");
 
    if (scanf("%d", &opcion) != 1) {       
        SetConsoleTextAttribute(hConsole, 12); // Rojo
        printf("*--------------------------*\n");
        printf("|##   ERROR DE ENTRADA   ##|\n");
        printf("*--------------------------*\n");
        SetConsoleTextAttribute(hConsole, 7);  // Color por defecto
        return 0;
    }

    if (opcion == 1) {
        SetConsoleTextAttribute(hConsole, 10); // Verde
        printf("*----------------------*\n");
        printf("|##   CAJA ABIERTA   ##|\n");
        printf("*----------------------*\n");
        SetConsoleTextAttribute(hConsole, 7);  // Color por defecto
        printf("*----------------------------------------------------------------------*\n");
        printf("|##                Mucha Suerte y Éxitos en su turno!                ##|\n");
        printf("*----------------------------------------------------------------------*\n");
        return 1;
    
    } else {
        SetConsoleTextAttribute(hConsole, 10);     
        printf("*-----------------------------------*\n");
        printf("|##       TURNO NO INICIADO       ##|\n");
        printf("|##   LA CAJA PERMANECE CERRADA   ##|\n");
        printf("*-----------------------------------*\n");
        SetConsoleTextAttribute(hConsole, 7);
        return 0;
    
    }
}
    
//Detalles de los productos para registrar en el carrito
struct factura{

    char marca[30];
    float precio;
    int stock;
    int necesidad;
    float iva;
};

//Funcion para poder mostrar el catalogo de productos
void mostrarCatalogo(struct productos lista[], int tamanioArreglo){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 5);
    printf("------------------------------------------------\n");
    printf("| ID |      Producto      |  Precio  |  Stock  |\n");
    printf("------------------------------------------------\n");
    SetConsoleTextAttribute(hConsole, 7);
    for (int i = 0; i < tamanioArreglo; i++) {
        printf("| %2d | %-18s | $%.2f | %7d |\n", i + 1, lista[i].marca, lista[i].precio, lista[i].stock);
    }
    printf("------------------------------------------------\n");
}

//Funcion para poder mostrar el carrito de compras
void mostrarCarrito(struct factura carrito[], int j){   
    printf("---------------------------------------------------\n");
    printf("| ID |      Producto      |  Precio  |  Cantidad  |\n");
    printf("---------------------------------------------------\n");
            
        for (int i = 0; i < j; i++) {
                
            printf("| %2d | %-18s | $%.2f | %7d |\n", i + 1, carrito[i].marca, carrito[i].precio, carrito[i].stock);
            
        }
                
        printf("---------------------------------------------------\n");
}

int crearPDF(struct factura carrito[], int j, char cliente[], long long int dni, float subtotal, float totalProductosIVA, float totalVentas){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // 1. Información del documento
    struct pdf_info info = {
        .creator = "Kaita Store",
        .producer = "Proyecto EPN",
        .title = "Factura cliente",
        .author = "Matthew Llerena & Kaya Alfusi",
        .subject = "Generacion de PDF",
        .date = "2026-01-23"
    };

    // 2. Crear el PDF (Tamaño A4)
    struct pdf_doc *pdf = pdf_create(PDF_A4_WIDTH, PDF_A4_HEIGHT, &info);
    if (!pdf) {
        printf("Error al crear el PDF\n");
        return 1;
    }

    // 3. Añadir una página
    pdf_append_page(pdf);

    // 4. Dibujar el Encabezado
    // El orden correcto para tu versión es: (pdf, página, texto, x, y, tamaño, color)
    pdf_add_text(pdf, NULL, "KAITA STORE RECEIPT", 12, 200, 800, PDF_BLACK);
    
    char lineaCliente[120];
    sprintf(lineaCliente, "Cliente: %s", cliente);
    pdf_add_text(pdf, NULL, lineaCliente, 12, 50, 750, PDF_BLACK);
    
    char lineaDni[50];
    sprintf(lineaDni, "Cédula: %I64d", dni);
    pdf_add_text(pdf, NULL, lineaDni, 12, 50, 730, PDF_BLACK);

    char fecha[40];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    strftime(fecha, sizeof(fecha), "Fecha: %d/%m/%Y  Hora: %H:%M", &tm);
    pdf_add_text(pdf, NULL, fecha, 12, 50, 710, PDF_BLACK);

    // 5. Dibujar una línea divisoria (Grosor 2)
    pdf_add_line(pdf, NULL, 50, 700, 545, 700, 2, PDF_BLACK);

    // 6. Cuerpo de la factura
    pdf_add_text(pdf, NULL, "Cant.  Producto                Uni.Precio   Subtotal", 10, 50, 690, PDF_BLACK);
    pdf_add_line(pdf, NULL, 50, 685, 545, 685, 1, PDF_BLACK);
    
    char lineaProductos[300];
    int y = 665;
    for (int i = 0; i < j; i++){
        sprintf(lineaProductos, "%-6d %-22s %11.2f %10.2f", carrito[i].stock, carrito[i].marca, carrito[i].precio, carrito[i].stock * carrito[i].precio);
        pdf_add_text(pdf, NULL, lineaProductos, 11, 50, y, PDF_BLACK);
        y -= 20;
    }
    // Agregar una línea divisoria de grosor 2 justo después del último producto
    pdf_add_line(pdf, NULL, 50, y + 10, 545, y + 10, 2, PDF_BLACK);

    // 7. Pie de factura
    int pie_y = y - 10; 
    char lineaSubtotal[50];
    char lineaIVA[50];
    char lineaTotal[50];
    sprintf(lineaSubtotal, "Subtotal: $%.2f", subtotal);
    sprintf(lineaIVA,     "IVA:      $%.2f", totalProductosIVA);
    sprintf(lineaTotal,   "Total:    $%.2f", totalVentas);

    pdf_add_text(pdf, NULL, lineaSubtotal, 12, 400, pie_y, PDF_BLACK);
    pdf_add_text(pdf, NULL, lineaIVA,     12, 400, pie_y - 20, PDF_BLACK);
    pdf_add_text(pdf, NULL, lineaTotal,   12, 400, pie_y - 40, PDF_BLACK);

    // 8. Guardar y cerrar
    static int num = 0;
    char lineaGuardar[20];
    sprintf(lineaGuardar, "Facturas/factura%d.pdf", num++);
    pdf_save(pdf, lineaGuardar);
    pdf_destroy(pdf);
    
    SetConsoleTextAttribute(hConsole, 10);
    printf("*--------------------------*\n");
    printf("| ¡PDF generado con exito! |\n");
    printf("*--------------------------*\n");
    SetConsoleTextAttribute(hConsole, 7);
    return 0;
}

int main(void){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    //Permitimos que se muestren caracteres especiales
    SetConsoleOutputCP(65001);
    int estadoCaja = 0;         // 0 = Cerrada     1 = Abierta
    int i = 0, j = 0;//Numero total de productos en el carrito
    int opcionSwitch, opcionIf;   
    int tamanioCarrito;

    float totalProductosIVA, totalProductosNoIVA, totalVentas, subtotal;
    float acumuladoSinIVA = 0, acumuladoIVA = 0, acumuladoConIVA = 0;
    
        
    int programaActivo = 1;
    float IVA = 0.15; //IVA estandar, pero que se puede modificar
    int tamanioArreglo;

    struct productos lista[100];
    struct factura carrito[10];

    //Añadimos los datos del inventario desde el archivo .csv        
    FILE * inventario;
    inventario = fopen("inventario.csv","r");

    if(inventario != NULL){
        char linea[100];
        while (fgets(linea, sizeof(linea), inventario)) {
            sscanf(linea, "%[^,],%d,%f,%d", lista[i].marca, &lista[i].stock, &lista[i].precio, &lista[i].necesidad);
            i++;
            tamanioArreglo = i;
        }
        fclose(inventario);
    } else{
        printf("NO se pudo abrir el archivo");
    }

    ordenarInventarioA_Z(lista, tamanioArreglo);

    //Apertura y cierre de caja
    while (1){ 
        // Si la caja está cerrada, preguntar si se desea abrir
        while (estadoCaja == 0) {
            estadoCaja = abrirCaja(estadoCaja);
            if (estadoCaja == 0) {
                printf("La caja está cerrada. Desea intentar abrirla (1=Si, 0=Salir): ");
                int seguir;
                if (scanf("%d", &seguir) != 1 || seguir == 0) {
                    printf("Gracias por usar nuestro cajero.\n");
                    return 0;
                }
            } else {
                // Si la caja se abrió, activar el programa
                programaActivo = 1;
            }
        }

        while(programaActivo){
            printf("\n");
            SetConsoleTextAttribute(hConsole, 5);
            printf("*------------------------------------------------------*\n");
            printf("|    #@#   Punto de venta express Kaita Store   #@#    |\n");
            printf("*------------------------------------------------------*\n");
            SetConsoleTextAttribute(hConsole, 7);
            printf("|Qué es lo que desea hacer?                            |\n");
            printf("|(1.) Añadir productos al carrito                      |\n");
            printf("|(2.) Borrar productos del carrito                     |\n");
            printf("|(3.) Lista de productos en el carrito                 |\n");
            printf("|(4.) Actualizar productos del catálogo                |\n");
            printf("|(5.) Añadir nuevos productos al catálogo              |\n");
            printf("|(6.) Exportar factura en PDF                          |\n");
            printf("|(7.) Cambiar el valor del IVA                         |\n");
            printf("|(8.) Entregar reporte general de la caja y cerrar caja|\n");
            printf("*------------------------------------------------------*\n");
            printf(">>");
            scanf("%d", &opcionSwitch);

            switch (opcionSwitch){
                //Añadir productos al carrito de compras
                case 1:
                    SetConsoleTextAttribute(hConsole, 13);
                    printf("\n");
                    printf("*-------------------------------------*\n");
                    printf("|##   AÑADIR PRODUCTOS AL CARRITO   ##|\n");
                    printf("*-------------------------------------*\n");
                    SetConsoleTextAttribute(hConsole, 7);
                    mostrarCatalogo(lista, tamanioArreglo);

                    //Límite por unidades totales en el carrito
                    while (1) {
                        int unidadesTotales = 0;
                        const int MAX_PRODUCTOS = 10;
                        
                        // Calcular el total de unidades en el carrito
                        for (int k = 0; k < j; k++) {
                            unidadesTotales += carrito[k].stock;
                        }

                        if (unidadesTotales >= MAX_PRODUCTOS) {
                            SetConsoleTextAttribute(hConsole, 12);
                            printf("*--------------------------------------------------*\n");
                            printf("|  CARRITO LLENO. No puedes agregar mas unidades.  |\n");
                            printf("*--------------------------------------------------*\n");
                            SetConsoleTextAttribute(hConsole, 7);
                            break;
                        }
                        
                        SetConsoleTextAttribute(hConsole, 5);
                        printf("*---------------------------------*\n");
                        printf("|   ¿Desea agregar un producto?   |\n");
                        printf("*---------------------------------*\n");
                        SetConsoleTextAttribute(hConsole, 7);
                        printf("|   (1.) SI                       |\n");
                        printf("|   (2.) NO                       |\n");
                        printf("*---------------------------------*\n>>");
                        scanf("%d", &opcionIf);

                        if (opcionIf == 2){
                            printf("*----------------------------*\n");
                            printf("|     Volviendo al menu...   |\n");
                            printf("*----------------------------*\n");
                            break;
                        }
                        else if(opcionIf == 1){
                            //Pedimos el ID y restamos 1 para concordar con el índice del arreglo
                            printf("*---------------------------------*\n");
                            printf("|     Digite el ID del producto   |\n");
                            printf("*---------------------------------*\n>>");
                            scanf("%d", &i);
                            i -= 1;

                            // Verificar si hay stock disponible en el catálogo
                            if (lista[i].stock <= 0) {
                                printf("No hay stock disponible de '%s' en el catalogo.\n", lista[i].marca);
                                printf("Elija otro producto o añada más al stock...\n");
                                continue;
                            }

                            int cantidadAgregar;
                            printf("*---------------------------------------------------------------------------------*\n");
                            printf("|  Cuantas unidades de '%s' desea agregar? Stock disponible: %d   |\n", lista[i].marca, lista[i].stock);
                            printf("*---------------------------------------------------------------------------------*\n>>");
                            scanf("%d", &cantidadAgregar);

                            if (cantidadAgregar <= 0) {
                                printf("*-------------------------*\n");
                                printf("|    Cantidad invalida    |\n");
                                printf("|    Vuelva a intentar    |\n");
                                printf("*-------------------------*\n");
                                continue;
                            }
                            if (cantidadAgregar > lista[i].stock) {
                                printf("No hay suficiente stock disponible.\nElija una cantidad entre 1 y %d\n", lista[i].stock);
                                continue;
                            }
                            if (unidadesTotales + cantidadAgregar > MAX_PRODUCTOS) {
                                printf("No puedes agregar mas unidades, el carrito excede el maximo permitido.\n");
                                printf("UNIDADES EN EL CARRITO: %d\n", unidadesTotales);
                                continue;
                            }

                            // Buscar si el producto ya está en el carrito
                            // No creamos un nuevo elemento, simplemente aumentamos la cantidad del elemento
                            int encontrado = 0;
                            for (int k = 0; k < j; k++) {
                                if (strcmp(carrito[k].marca, lista[i].marca) == 0) {
                                    carrito[k].stock += cantidadAgregar; //Incrementa el stock en el carrito
                                    lista[i].stock -= cantidadAgregar;   //Resta el stock en el catálogo
                                    if (lista[i].stock == 0) {
                                        SetConsoleTextAttribute(hConsole, 12);
                                        printf("*----------------------------------------------------------------------------*\n");
                                        printf("|   ALERTA!! Ya no quedan unidades de %s en el catalogo...   |\n", lista[i].marca);
                                        printf("*----------------------------------------------------------------------------*\n");
                                        SetConsoleTextAttribute(hConsole, 7);
                                    }
                                    encontrado = 1;
                                    break;
                                }
                            }

                            //Si no está en el carrito se lo añade
                            if (!encontrado) {
                                strcpy(carrito[j].marca, lista[i].marca);
                                carrito[j].precio = lista[i].precio;
                                carrito[j].necesidad = lista[i].necesidad;
                                carrito[j].stock = cantidadAgregar;
                                lista[i].stock -= cantidadAgregar;
                                if (lista[i].stock == 0) {
                                    SetConsoleTextAttribute(hConsole, 12);
                                    printf("*----------------------------------------------------------------------------*\n");
                                    printf("|   ALERTA!! Ya no quedan unidades de %s en el catalogo...   |\n", lista[i].marca);
                                    printf("*----------------------------------------------------------------------------*\n");
                                    SetConsoleTextAttribute(hConsole, 7);
                                }
                                j++;
                            }
                        } else{
                            printf("*----------------------------------------------------------*");
                            printf("|  No es una opcion valida, regresando al menu inicial...  |\n");
                            printf("*----------------------------------------------------------*");
                        }
                    }
                    tamanioCarrito = j;
                    break;
                //Borrar productos del carrito
                case 2:
                    mostrarCarrito(carrito, tamanioCarrito);
                    
                    printf("\nDesea borrar algun producto?\n");
                    printf("1 -> SI\n");
                    printf("2 -> NO\n");
                    printf(">>");
                    scanf("%d", &opcionIf);

                    if (opcionIf == 2){
                        printf("\n");
                        printf("*----------------------------*\n");
                        printf("|     Volviendo al menu...   |\n");
                        printf("*----------------------------*\n\n");
                        break;
                    } else if(opcionIf == 1){
                        int unidadesBorrar;
                        printf("\nDigite el ID del producto que deseaa borrar: \n");
                        printf(">>");
                        scanf("%d", &i);
                        i -= 1;

                        if (( i >= 0 ) && ( i <= j )){
                            printf("Cuantas unidades de %s desea borrar, actualmente tiene %d\n", carrito[i].marca, carrito[i].stock);
                            printf(">>");
                            scanf("%d", &unidadesBorrar);

                            if (unidadesBorrar <= carrito[i].stock){
                                lista[i].stock += unidadesBorrar; //Regresamos los items al inventario
                                carrito[i].stock -= unidadesBorrar; //Borramos la cantidad deseada del carrito
                                
                                //En caso de que el stock se haga 0, borra el producto de la lista del carrito
                                if (carrito[i].stock == 0){
                                    for (int k = i; k < j - 1; k++){
                                        carrito[k] = carrito [k + 1];
                                    }
                                    j--;
                                }
                                printf("\nCarrito actualizado correctamente\n");
                                printf("\nVolviendo al menu...\n\n");
                            } else{
                                printf("No se pueden borrar mas unidades de las que hay");
                                printf("\nVolviendo al menu...\n\n");
                            }
                        } else{
                            printf("Este ID no es valido");
                            printf("\nVolviendo al menu...\n\n");
                            break;
                        }
                    } else{
                        printf("No es una opcion válida, vuelva a intentar...");
                    }
                    break;
                //Lista de productos en el carrito
                case 3:
                    mostrarCarrito(carrito, tamanioCarrito);
                    printf("\nVolviendo al menu...\n\n");
                    break;
                //Actualizar productos del catálogo
                case 4:
                    mostrarCatalogo(lista, tamanioArreglo);

                    printf("\nDesea actualizar algun producto?\n");
                    printf("1 -> SI\n");
                    printf("2 -> NO\n");
                    printf(">>");
                    scanf("%d", &opcionIf);

                    if (opcionIf == 2){
                        printf("\n");
                        printf("*----------------------------*\n");
                        printf("|     Volviendo al menu...   |\n");
                        printf("*----------------------------*\n\n");
                        break;
                    }
                    else if(opcionIf == 1){
                        int stockActualizar;  //Unidades a actualizar
                        float precioActualizar; //Actualizar a un nuevo precio
                        
                        printf("\nDigite el ID del producto que deseaa actualizar: \n");
                        printf(">>");
                        scanf("%d", &i);

                        i -= 1;

                        if ( ( i >= 0 ) && ( i <= tamanioArreglo ) ){
                            printf("El precio actual de %s es de $%.2f, que nuevo precio desea poner?\n", lista[i].marca, lista[i].precio);
                            printf(">>");
                            scanf("%f", &precioActualizar);

                            if (precioActualizar >= 0.00){
                                lista[i].precio = precioActualizar;    //Actualizamos el stock
                            } else{
                                printf("La cantidad a ingresar debe ser mayor o igual que cero");
                                printf("\nVolviendo al menu...\n\n");
                            }
                                
                            printf("Cuantas unidades de %s desea poner, actualmente tiene %d\n", lista[i].marca, lista[i].stock);
                            printf(">>");
                            scanf("%d", &stockActualizar);

                            if (stockActualizar >= 0){
                                lista[i].stock = stockActualizar;    //Actualizamos el stock
                                printf("\nCatalogo actualizado correctamente\n");
                                printf("\nVolviendo al menu...\n\n");
                            }else{
                                printf("La cantidad a ingresar debe ser mayor o igual que cero");
                                printf("\nVolviendo al menu...\n\n");                                
                            }
                        } else{
                            printf("Este ID no es valido");
                            printf("\nVolviendo al menu...\n\n");
                            break;
                        }
                    }
                    else{
                        printf("No es una opcion válida, vuelva a intentar...");
                    }

                    //Cada que se actualice un producto, actualizar en el archivo inventario.csv
                    inventario = fopen("inventario.csv","w");
                    if (inventario == NULL) {
                        printf("No se pudo abrir el archivo para agregar.\n");
                        break;
                    }

                    for(i = 0; i < tamanioArreglo; i++){
                        fprintf(inventario, "%s,%d,%.2f,%d\n", lista[i].marca, lista[i].stock, lista[i].precio, lista[i].necesidad);
                    }

                    fclose(inventario);
                    break;
                //Añadir nuevos productos al catálogo
                case 5:
                    mostrarCatalogo(lista, tamanioArreglo);
                    inventario = fopen("inventario.csv","a");
                    if (inventario == NULL) {
                        printf("No se pudo abrir el archivo para agregar.\n");
                        break;
                    }

                    getchar();
                    printf("Ingrese el nombre del producto que añadirá:\n>>");
                    scanf("%[^\n]", lista[i].marca);

                    //Verificamos si el producto existe en el catalogo
                    //APLICAR BUSQUEDA BINARIA
                    
                    
                    int repetido = buscarProducto(lista, tamanioArreglo, i);;
                    
                    if (repetido) {
                        printf("Este producto ya existe, no se puede agregar.\n");
                        fclose(inventario);
                        break;
                    }

                    printf("Ingrese el precio:\n>>");
                    scanf("%f", &lista[i].precio);
                    printf("Ingrese el stock:\n>>");
                    scanf("%d", &lista[i].stock);
                    printf("Ingrese la necesidad (0 básico, 1 impulso):\n>>");
                    scanf("%d", &lista[i].necesidad);

                    fprintf(inventario, "%s,%d,%.2f,%d\n", lista[i].marca, lista[i].stock, lista[i].precio, lista[i].necesidad);
                    fclose(inventario);
                    i++; // Actualiza el tamaño de la lista
                    tamanioArreglo = i;
                    printf("*----------------------------------*\n");
                    printf("| Producto agregado correctamente. |\n");
                    printf("*----------------------------------*\n");
                    printf("---------------------------------------------------------------\n");
                    
                    ordenarInventarioA_Z(lista, tamanioArreglo);
                    //Volver a sobreescribir en el archivo con el nuevo elemento ya ordenado
                    inventario = fopen("inventario.csv","w");
                    if (inventario == NULL) {
                        printf("No se pudo abrir el archivo para agregar.\n");
                        break;
                    }

                    for(i = 0; i < tamanioArreglo; i++){
                        fprintf(inventario, "%s,%d,%.2f,%d\n", lista[i].marca, lista[i].stock, lista[i].precio, lista[i].necesidad);
                    }
                    fclose(inventario);
                    break;
                //Facturar productos, Creacion de factura en PDF
                case 6:
                    totalProductosIVA = 0;      //Solo la suma del IVA
                    totalProductosNoIVA = 0;    //Solo la suma de los precios sin IVA
                    totalVentas = 0;
                    subtotal = 0;

                    char cliente[100];
                    long long int dni;
                    
                    printf("Digite el nombre del cliente:\n>>");
                    getchar();
                    fgets(cliente, sizeof(cliente), stdin);
                    printf("Digite el DNI del cliente:\n>>");
                    scanf("%I64d", &dni);

                    for ( i = 0; i < j; i++){
                        //Calculamos el subtotal de la compra (sin IVA)
                        totalProductosNoIVA = (carrito[i].stock * carrito[i].precio);
                        subtotal += totalProductosNoIVA;
                    }
                
                    for ( i = 0; i < j; i++){
                        if (carrito[i].necesidad == 1){
                            //Calculamos unicamente el IVA de cada producto ingresado
                            carrito[i].iva = (carrito[i].stock * carrito[i].precio) * IVA;
                            totalProductosIVA += carrito[i].iva;
                        }
                    }

                    totalVentas = subtotal + totalProductosIVA;
                    acumuladoSinIVA += subtotal;
                    acumuladoIVA += totalProductosIVA;
                    acumuladoConIVA += totalVentas;     

                    crearPDF(carrito, j, cliente, dni, subtotal, totalProductosIVA, totalVentas);

                    //Finalizada la venta borramos el carrito actual para que se pueda generar una nueva venta
                
                    for (int k = 0; k < j; k++) {
                        carrito[k].stock = 0;
                        carrito[k].precio = 0;
                        carrito[k].necesidad = 0;
                        strcpy(carrito[k].marca, "");
                    }
                    j = 0;
                    
                    printf("\n## Carrito vaciado. Listo para la siguiente venta. ##\n");
                    
                    //Despues de confirmar la venta
                    //Actualizamos el inventario.csv con los productos que quedan
                    inventario = fopen("inventario.csv","w");
                    if (inventario == NULL) {
                        printf("No se pudo abrir el archivo para agregar.\n");
                        break;
                    }

                    for(i = 0; i < tamanioArreglo; i++){
                        fprintf(inventario, "%s,%d,%.2f,%d\n", lista[i].marca, lista[i].stock, lista[i].precio, lista[i].necesidad);
                    }

                    fclose(inventario);
                    break;
                //Cambiar el valor del IVA
                case 7: {
                    //Variable temporal para tratar con el valor ingresado
                    //y con el valor que se usará en el programa
                    int IVAtemp;
                    
                    printf("El IVA actual es del %.0f%%\n", IVA * 100);
                    printf("Digite un valor entero entre el 0 y 100 del IVA deseado\n>>");
                    scanf("%d", &IVAtemp);

                    //Validamos que el IVA sea un valor razonable
                    if ( IVAtemp > 0 && IVAtemp <= 100){
                        printf("EL nuevo IVA es del %d%%\n", IVAtemp);
                        IVA = IVAtemp / 100.0;
                    } else{
                        printf("El valor ingresado no es valido, vuelta a intentar.\n");
                    }
                    break;
                }
                //Entregar reporte general de la caja y cerrarla ############
                case 8:
                    //Mostramos una alerta en caso de haber menos de 5 productos en el catalogo
                    for ( i = 0; i < 20; i++){
                    
                        if (lista[i].stock <= 5){
                        
                            printf("\nAlerta!!.. Stock bajo del producto '%s', quedan %d unidades\n", lista[i].marca, lista[i].stock);
                        
                        }
                    }
                
                    printf("\n--- REPORTE TOTAL DE VENTAS DEL TURNO ---\n");
                    printf("Total ventas sin IVA: $%.2f\n", acumuladoSinIVA);
                    printf("Total ventas con IVA: $%.2f\n", acumuladoConIVA);
                    printf("Total IVA recaudado: $%.2f\n", acumuladoIVA);
                    printf("Total recaudado en el turno: $%.2f\n", acumuladoConIVA);


                    printf("\n\nGracias por usar nuestro punto de venta :)\n\n");
                    estadoCaja = 0;
                    programaActivo = 0;
                    // Al cerrar la caja, volver al bucle principal para preguntar si se desea abrirla de nuevo
                    continue;
                default:
                    printf("Opcion inválida :(\n");
                    break;
            }
        }
    }    
    return 0;        
}