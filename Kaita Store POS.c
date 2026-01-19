#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define IVA 0.15    // (15%  -> 0.15)  (8% -> 0.08)    (0% -> 0.00)
#include <windows.h>

//Funcion para abrir la caja o mantenerla cerrada
//Encargada de dar paso a que funcione todo el programa
int abrirCaja(int estadoCaja) {
    
    int opcion;

    if (estadoCaja == 1) {
        
        printf("\n##  CAJA ABIERTA  ##\n");
        printf("Muchos exitos en su turno\n");
        return 1;
    
    }

    //Si estadoCaja == 0 pues la caja inicialmente esta cerrada
    printf("\n##  CAJA CERRADA  ##\n");
    printf("Digite 1 para abrirla y empezar el turno (0 para cancelar): \n");
    printf(">>");
 
    if (scanf("%d", &opcion) != 1) {
        
        printf("Error de entrada.\n\n");
        return 0;

    }

    if (opcion == 1) {
        
        printf("\n##  CAJA ABIERTA  ##\n");
        printf("Muchos exitos en su turno\n\n");
        return 1;
    
    } else {
        
        printf("\n##  TURNO NO INICIADO  ##\n");
        printf("\nLa caja permanece cerrada.\n\n");
        return 0;
    
    }
}

//Detalles de los productos en el catalogo
struct productos{    
    
    char marca[30];
    float precio;
    int stock;
    int necesidad;
    float iva;
};

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
    
    printf("------------------------------------------------\n");
    printf("| ID |      Producto      |  Precio  |  Stock  |\n");
    printf("------------------------------------------------\n");
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

int main(void){
    //Permitimos que se muestren caracteres especiales
    SetConsoleOutputCP(65001);
    int estadoCaja = 0;         // 0 = Cerrada     1 = Abierta
    int i = 0, j = 0, opcionSwitch, opcionIf;   //j será el numero total de productos
    float totalProductosIVA, totalProductosNoIVA, totalVentas, subtotal;
    float acumuladoSinIVA = 0, acumuladoIVA = 0, acumuladoConIVA = 0;
    const int MAX_PRODUCTOS = 10;  
        
    int programaActivo = 1;

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
        }
        fclose(inventario);
    } else{
        printf("NO se pudo abrir el archivo");
    }

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
            }
        }

        while(programaActivo){
            printf("\n\n");
            printf("*---------------------------------------------*\n");
            printf("*|    Punto de venta express Kaita Store     |*\n");
            printf("*---------------------------------------------*\n");
            printf("\n");
            printf("Qué es lo que desea hacer?\n");
            printf("1. Añadir productos al carrito\n");
            printf("2. Borrar productos del carrito\n");
            printf("3. Lista de productos en el carrito\n");
            printf("4. Actualizar productos del catálogo\n");
            printf("5. Añadir nuevos productos al catálogo\n");
            printf("6. Facturar productos\n");
            printf("7. Entregar reporte general de la caja y cerrar caja\n");
            printf("8. Cambiar el valor del IVA\n>>");
            scanf("%d", &opcionSwitch);

            switch (opcionSwitch){
                case 1:
                    mostrarCatalogo(lista, i);
                    break;
                case 2:
                    printf("1\n");
                    break;
                case 3:
                    printf("1\n");
                    break;
                case 4:
                    /*
                    mostrarCatalogo(lista);

                    printf("\nDesea actualizar algun producto?\n");
                    printf("1 -> SI\n");
                    printf("2 -> NO\n");
                    printf(">>");
                    scanf("%d", &opcionIf);

                    if (opcionIf == 2){
                                
                        printf("\nVolviendo al menu...\n\n");

                        goto inicio;    //Regresamos al menu de opciones del punto de venta

                    }
                    else if(opcionIf == 1){
                            
                        int stockActualizar;  //Unidades a actualizar
                        float precioActualizar; //Actualizar a un nuevo precio
                        
                        printf("\nDigite el ID del producto que deseaa actualizar: \n");
                        printf(">>");
                        scanf("%d", &i);

                        i -= 1;

                        if ( ( i >= 0 ) && ( i <= 20 ) ){

                            printf("El precio actual de %s es de $%.2f, que nuevo precio desea poner?\n", lista[i].marca, lista[i].precio);
                            printf(">>");
                            scanf("%f", &precioActualizar);

                            if (precioActualizar >= 0.00){
                                    
                                lista[i].precio = precioActualizar;    //Actualizamos el stock
                                    
                            }
                            else{

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
                                    
                            }
                            else{

                                printf("La cantidad a ingresar debe ser mayor o igual que cero");
                                printf("\nVolviendo al menu...\n\n");
                                

                            }



                        }
                        else{
                                
                            printf("Este ID no es valido");
                            printf("\nVolviendo al menu...\n\n");
                                
                                
                        }

                            
                        goto inicio;

                    }
                    else{

                        printf("No es una opcion válida, vuelva a intentar...");

                    }
                    */
                    break;
                case 5:
                    mostrarCatalogo(lista, i);
                    inventario = fopen("inventario.csv","a");
                    if (inventario == NULL) {
                        printf("No se pudo abrir el archivo para agregar.\n");
                        break;
                    }

                    getchar();
                    printf("Ingrese el nombre del producto:\n>>");
                    scanf("%[^\n]", lista[i].marca);

                    //Verificamos si el producto existe
                    int repetido = 0;
                    for (int j = 0; j < i; j++) {
                        if (strcmp(lista[i].marca, lista[j].marca) == 0) {
                            repetido = 1;
                            break;
                        }
                    }
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
                    printf("Producto agregado correctamente.\n");
                    break;
                case 6:
                    printf("1\n");
                    break;
                case 7:
                    printf("1\n");
                    programaActivo = 0;
                    break;
                
                case 8:
                    
                    break;
            
                default:
                    printf("Opcion inválida :(\n");
                    break;
            }
        }
    }    
    return 0;        
}