OUT := out.txt
SALIDA-CATEDRA:= salida_catedra.txt
COMBINACIONALES := combinacionales.circ

all : comparacion

$(OUT): $(COMBINACIONALES)
	@echo "El archivo $(OUT) no existe"; \
	echo "Creando archivo..."; \
	logisim-evolution --toplevel-circuit "verificador" -tty table $(COMBINACIONALES) > $(OUT); \
	echo "Archivo $(OUT) creado. Comparando archivos..."; \
	
comparacion :  $(SALIDA-CATEDRA) $(OUT)
	@if diff -s $(SALIDA-CATEDRA) $(OUT) > /dev/null; then \
		echo "Los archivos son iguales"; \
	else \
		echo "Los archivos no son iguales"; \
	fi

.PHONY : comparacion all
