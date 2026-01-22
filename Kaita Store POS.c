#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>

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

//Funcion para verificar si es que el cliente está afiliado a la tienda
void verificarAfiliacion(long long int CI){

    int cantidadDocumentos = 300;
    long long int arr[500];
    int afiliado = 0;
    char nombre[100];

    FILE * afiliacion;
    afiliacion = fopen("afiliacion.csv","r");

    if(afiliacion != NULL){
        for (int i = 0; i < cantidadDocumentos; i++){
            fscanf(afiliacion, "%I64d,%[^\n]\n", &arr[i], nombre);
            if(CI == arr[i]){
                afiliado = 1;
                break;
            }
        }
        
        if(afiliado == 1){
            printf("El cliente %s está afiliado", nombre);
        }
        else{
            printf("El cliente no está afiliado");
        }
        fclose(afiliacion);
    } else{
        printf("No se pudo abrir el archivo");
    }
}

int main(void){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    //Permitimos que se muestren caracteres especiales
    SetConsoleOutputCP(65001);
    int estadoCaja = 0;         // 0 = Cerrada     1 = Abierta
    int i = 0, j = 0;           //j será el numero total de productos
    int opcionSwitch, opcionIf;   
    
    float totalProductosIVA, totalProductosNoIVA, totalVentas, subtotal;
    float acumuladoSinIVA = 0, acumuladoIVA = 0, acumuladoConIVA = 0;
    
    
        
    int programaActivo = 1;
    float IVA = 0.15; //IVA estandar, pero que se puede modificar
    long long int documentoIdentidad;
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
            printf("|(6.) Facturar productos                               |\n");
            printf("|(7.) Entregar reporte general de la caja y cerrar caja|\n");
            printf("|(8.) Cambiar el valor del IVA                         |\n");
            printf("*------------------------------------------------------*\n");
            printf(">>");
            scanf("%d", &opcionSwitch);

            switch (opcionSwitch){
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
                            printf("CARRITO LLENO. No puedes agregar mas unidades.\n");
                            break;
                        }

                        printf("Desea agregar un producto?\n");
                        printf("1. SI\n2. NO\n>>");
                        scanf("%d", &opcionIf);

                        if (opcionIf == 2){
                            printf("Volviendo al menu inicial...");
                            break;
                        }
                        else if(opcionIf == 1){
                            //Pedimos el ID y restamos 1 para concordar con el índice del arreglo
                            printf("Digite su ID:\n");
                            printf(">>");
                            scanf("%d", &i);
                            i -= 1;

                            // Verificar si hay stock disponible en el catálogo
                            if (lista[i].stock <= 0) {
                                printf("No hay stock disponible de '%s' en el catalogo.\n", lista[i].marca);
                                printf("Elija otro producto o añada más al stock...\n");
                                continue;
                            }

                            int cantidadAgregar;
                            printf("Cuantas unidades de '%s' desea agregar? Stock disponible: %d\n>>", lista[i].marca, lista[i].stock);
                            scanf("%d", &cantidadAgregar);

                            if (cantidadAgregar <= 0) {
                                printf("Cantidad invalida.\nVuelva a intentar...");
                                continue;
                            }
                            if (cantidadAgregar > lista[i].stock) {
                                printf("No hay suficiente stock disponible.\nElija una cantidad entre 1 y %d", lista[i].stock);
                                continue;
                            }
                            if (unidadesTotales + cantidadAgregar > MAX_PRODUCTOS) {
                                printf("No puedes agregar mas unidades, el carrito excede el maximo permitido.");
                                continue;
                            }

                            // Buscar si el producto ya está en el carrito
                            int encontrado = 0;
                            for (int k = 0; k < j; k++) {
                                if (strcmp(carrito[k].marca, lista[i].marca) == 0) {
                                    carrito[k].stock += cantidadAgregar; //Incrementa el stock en el carrito
                                    lista[i].stock -= cantidadAgregar;   //Resta el stock en el catálogo
                                    if (lista[i].stock == 0) {
                                        printf("Ya no quedan unidades de %s en el catalogo...\n", lista[i].marca);
                                    }
                                    encontrado = 1;
                                    break;
                                }
                            }

                            //Sino está en el carrito, se lo añade
                            if (!encontrado) {
                                strcpy(carrito[j].marca, lista[i].marca);
                                carrito[j].precio = lista[i].precio;
                                carrito[j].necesidad = lista[i].necesidad;
                                carrito[j].stock = cantidadAgregar;
                                lista[i].stock -= cantidadAgregar;
                                if (lista[i].stock == 0) {
                                    printf("Ya no quedan unidades de %s en el catalogo...\n", lista[i].marca);
                                }
                                j++;
                            }
                        } else{
                            printf("No es una opcion valida, regresando al menu inicial...\n");
                        }
                    }
                    break;
                case 2:
                    printf("1\n");
                    break;
                case 3:
                    printf("1\n");
                    break;
                case 4:
                    mostrarCatalogo(lista, tamanioArreglo);

                    printf("\nDesea actualizar algun producto?\n");
                    printf("1 -> SI\n");
                    printf("2 -> NO\n");
                    printf(">>");
                    scanf("%d", &opcionIf);

                    if (opcionIf == 2){
                        printf("\nVolviendo al menu...\n\n");
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
                    tamanioArreglo = i;
                    printf("*----------------------------------*\n");
                    printf("| Producto agregado correctamente. |\n");
                    printf("*----------------------------------*\n");
                    printf("---------------------------------------------------------------\n");
                    break;
                case 6:
                    printf("Digite la cedula afiliada:\n>>");
                    scanf("%I64d", &documentoIdentidad);
                    verificarAfiliacion(documentoIdentidad);
                    break;
                case 7:
                    printf("1\n");
                    programaActivo = 0;
                    break;
                
                case 8: {
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
                default:
                    printf("Opcion inválida :(\n");
                    break;
            }
        }
    }    
    return 0;        
}