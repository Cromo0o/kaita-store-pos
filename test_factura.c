#include <stdio.h>
#include "pdfgen.h"

int main() {
    // 1. Información del documento
    struct pdf_info info = {
        .creator = "Sistema de Ventas C",
        .producer = "Proyecto EPN",
        .title = "Factura de Prueba",
        .author = "Matthew Llerena",
        .subject = "Generacion de PDF",
        .date = "2026-01-22"
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
    pdf_add_text(pdf, NULL, "FACTURA COMERCIAL", 12, 200, 800, PDF_BLACK);
    pdf_add_text(pdf, NULL, "Cliente: Matthew Llerena", 12, 50, 750, PDF_BLACK);
    pdf_add_text(pdf, NULL, "Fecha: 22 de Enero, 2026", 12, 50, 730, PDF_BLACK);

    // 5. Dibujar una línea divisoria (Grosor 2)
    pdf_add_line(pdf, NULL, 50, 715, 545, 715, 2, PDF_BLACK);

    // 6. Cuerpo de la factura
    pdf_add_text(pdf, NULL, "Cant.   Descripcion              Precio    Total", 10, 50, 690, PDF_BLACK);
    pdf_add_line(pdf, NULL, 50, 685, 545, 685, 1, PDF_BLACK);
    
    pdf_add_text(pdf, NULL, "1       Mouse Gamer RGB         $25.00    $25.00", 11, 50, 665, PDF_BLACK);
    pdf_add_text(pdf, NULL, "2       Teclado Mecanico        $45.00    $90.00", 11, 50, 645, PDF_BLACK);

    // 7. Pie de factura
    pdf_add_line(pdf, NULL, 400, 600, 545, 600, 1, PDF_BLACK);
    pdf_add_text(pdf, NULL, "TOTAL: $115.00", 12, 400, 580, PDF_BLACK);

    // 8. Guardar y cerrar
    pdf_save(pdf, "factura_final.pdf");
    pdf_destroy(pdf);

    printf("¡PDF generado con exito! Revisa el archivo 'factura_final.pdf'\n");

    return 0;
}