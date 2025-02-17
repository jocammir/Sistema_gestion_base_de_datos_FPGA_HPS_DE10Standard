#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"


int main (void)
{
	alt_up_char_buffer_dev *dev1;
	alt_up_char_buffer_init(dev1);

	dev1 = alt_up_char_buffer_open_dev("/dev/video_character_buffer_with_dma_0");
	alt_up_char_buffer_clear(dev1);
	volatile int * KEY_ptr = (int *) 0x00005000; // botonera
	volatile int * contador = (int *) 0x00000000; // contador
	int * memoria = (int *) 0x00010000; //memoria
	int botonera;


	char input[100];
	char time[100];
	char * text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi porta, eros nec scelerisque pulvinar, erat arcu porta augue, et semper sem nibh in est. Donec porttitor aliquet mauris et vestibulum. Donec mollis, libero ut pellentesque aliquet, justo metus hendrerit urna, id fermentum ligula dolor laoreet elit. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Etiam nec odio libero. Sed ut mattis nulla. Nam blandit pretium dolor id scelerisque. Sed vel lacus varius, tincidunt lorem ac, facilisis nisl. Fusce sollicitudin in dui et convallis. Mauris ultrices magna a posuere viverra. Pellentesque commodo elementum tempus. Donec et gravida mauris. Mauris leo lorem, consequat quis neque a, placerat efficitur turpis. Mauris efficitur varius nunc, tempus facilisis nibh molestie id. In fermentum lectus eget vulputate venenatis. Aenean facilisis risus nunc, eu mattis arcu auctor vitae. Aliquam et malesuada erat. Donec molestie, lorem in ultrices hendrerit, magna est sodales lorem, ut facilisis sem lorem sit amet quam. Phasellus faucibus turpis ut arcu posuere, in imperdiet arcu gravida. Integer diam purus, porttitor sed mi non, porttitor elementum orci. Morbi pretium malesuada nulla nec mollis. Quisque imperdiet libero lectus, ut consectetur ipsum cursus et. Mauris sit amet dolor id risus aliquam porta. Donec et luctus dolor, nec dictum leo. Quisque pellentesque pharetra turpis ac semper. Etiam porttitor at orci nec consectetur. Duis at eleifend tellus. Aenean vitae elit tempus, egestas nibh a, vestibulum neque. Ut ante erat, varius a rhoncus et, pellentesque at ligula. Curabitur lobortis non elit quis ullamcorper. Curabitur ut aliquam neque. Sed laoreet eget eros nec maximus. Vivamus commodo orci eget velit pretium sollicitudin. Cras ut scelerisque orci. Aenean sollicitudin velit a ipsum vehicula aliquam. Praesent ullamcorper, odio faucibus fermentum vulputate, leo nisl tincidunt ante, sed faucibus nibh justo et ipsum. Sed sed tempus risus. Nam dapibus vitae lectus bibendum porta. Nullam sit amet massa porttitor dui sodales pretium in non erat. Phasellus bibendum felis turpis, at congue risus dictum et. Mauris suscipit posuere est, vitae iaculis libero accumsan id. Fusce luctus odio quis porttitor dapibus. Suspendisse placerat odio vitae pellentesque interdum. Nunc consectetur, erat iaculis congue aliquam, lectus leo finibus metus, vel laoreet mi purus vel lacus. Aliquam sed turpis lacus. Sed viverra aliquet nulla, in aliquam nunc ultrices nec. Cras scelerisque in ligula vitae elementum. Nam odio est, interdum et tristique eu, placerat eget tortor. In scelerisque commodo lectus ultricies malesuada. Nulla sodales dapibus felis, ut tincidunt risus cursus non. Pellentesque vel ante eu justo facilisis porttitor sit amet eu libero. Mauris aliquam gravida euismod. Ut sodales euismod urna. Donec nec urna ut odio eleifend convallis at at leo.";
	IOWR(memoria,0x00011000,text);
	while (1){
		//printf("El resultado es: %d\n",*(contador+2));

		botonera = *(KEY_ptr);
		//printf("%d\n",botonera);
		*(contador+1)=0;
		*(contador)=4;
		*(contador)=2;
		alt_up_char_buffer_string(dev1, "Presione una botonera para realizar la consulta: ", 0,5);
		if(botonera == 3){
			alt_up_char_buffer_clear(dev1);
			sprintf(time, "%d", *(contador+2));
			char * read = IORD(memoria,0x00011000);
			printf(read);
			/*int numero = 2;
			char decode[100];
			itoa(read, decode,10);*/
			//sprintf(texto, "%d", read);
			alt_up_char_buffer_string(dev1, "Botonera 3 accionada:", 0,0);
			alt_up_char_buffer_string(dev1, read, 0,1);
			alt_up_char_buffer_string(dev1, "En el segundo: ", 0,3);
			alt_up_char_buffer_string(dev1, time, 17,3);


		}
		if(botonera == 5) {
			alt_up_char_buffer_clear(dev1);
			sprintf(time, "%d", *(contador+2));

			alt_up_char_buffer_string(dev1, "Botonera 2 accionada:", 0,0);
			alt_up_char_buffer_string(dev1, "Aqui deberia salir la consulta numero 2", 0,1);
			alt_up_char_buffer_string(dev1, "En el segundo: ", 0,3);
			alt_up_char_buffer_string(dev1, time, 17,3);

		}
		if(botonera == 6) {
			alt_up_char_buffer_clear(dev1);
			sprintf(time, "%d", *(contador+2));

			alt_up_char_buffer_string(dev1, "Botonera 1 accionada:", 0,0);
			alt_up_char_buffer_string(dev1, "Aqui deberia salir la consulta numero 1", 0,1);
			alt_up_char_buffer_string(dev1, "En el segundo: ", 0,3);
			alt_up_char_buffer_string(dev1, time, 17,3);
		}

/*
		printf("Ingrese texto: ");

		fgets(input, 100, stdin);

	    alt_up_char_buffer_string(dev1, input, 0,0);
	    usleep(2000000);*/
		if(botonera == 6 || botonera == 5 || botonera ==3)
		{
			usleep(4000000);
			alt_up_char_buffer_clear(dev1);
		}

	}
}
