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

	volatile int * SW_switch_ptr = (int *) 0x00004000;
	volatile int * contador = (int *) 0x00001010; // contador
	int * memoria = (int *) 0x00080000; //memoria
	int SW_value;

	char input[100];
	char time[100];
	char * text = "XXTexto de Prueba: Lorem ipsum dolor sit amet \nconsectetur adipiscing elit. Morbi porta, eros nec scelerisque pulvinar, erat arcu porta augue, et semper sem nibh in est. Donec porttitor aliquet mauris et vestibulum. Donec mollis, libero ut pellentesque aliquet, justo metus hendrerit urna, id fermentum ligula dolor laoreet elit. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Etiam nec odio libero. Sed ut mattis nulla. Nam blandit pretium dolor id scelerisque. Sed vel lacus varius, tincidunt lorem ac, facilisis nisl. Fusce sollicitudin in dui et convallis. Mauris ultrices magna a posuere viverra. Pellentesque commodo elementum tempus. Donec et gravida mauris. Mauris leo lorem, consequat quis neque a, placerat efficitur turpis. Mauris efficitur varius nunc, tempus facilisis nibh molestie id. In fermentum lectus eget vulputate venenatis. Aenean facilisis risus nunc, eu mattis arcu auctor vitae. Aliquam et malesuada erat. Donec molestie, lorem in ultrices hendrerit, magna est sodales lorem, ut facilisis sem lorem sit amet quam. Phasellus faucibus turpis ut arcu posuere, in imperdiet arcu gravida. Integer diam purus, porttitor sed mi non, porttitor elementum orci. Morbi pretium malesuada nulla nec mollis. Quisque imperdiet libero lectus, ut consectetur ipsum cursus et. Mauris sit amet dolor id risus aliquam porta. Donec et luctus dolor, nec dictum leo. Quisque pellentesque pharetra turpis ac semper. Etiam porttitor at orci nec consectetur. Duis at eleifend tellus. Aenean vitae elit tempus, egestas nibh a, vestibulum neque. Ut ante erat, varius a rhoncus et, pellentesque at ligula. Curabitur lobortis non elit quis ullamcorper. Curabitur ut aliquam neque. Sed laoreet eget eros nec maximus. Vivamus commodo orci eget velit pretium sollicitudin. Cras ut scelerisque orci. Aenean sollicitudin velit a ipsum vehicula aliquam. Praesent ullamcorper, odio faucibus fermentum vulputate, leo nisl tincidunt ante, sed faucibus nibh justo et ipsum. Sed sed tempus risus. Nam dapibus vitae lectus bibendum porta. Nullam sit amet massa porttitor dui sodales pretium in non erat. Phasellus bibendum felis turpis, at congue risus dictum et. Mauris suscipit posuere est, vitae iaculis libero accumsan id. Fusce luctus odio quis porttitor dapibus. Suspendisse placerat odio vitae pellentesque interdum. Nunc consectetur, erat iaculis congue aliquam, lectus leo finibus metus, vel laoreet mi purus vel lacus. Aliquam sed turpis lacus. Sed viverra aliquet nulla, in aliquam nunc ultrices nec. Cras scelerisque in ligula vitae elementum. Nam odio est, interdum et tristique eu, placerat eget tortor. In scelerisque commodo lectus ultricies malesuada. Nulla sodales dapibus felis, ut tincidunt risus cursus non. Pellentesque vel ante eu justo facilisis porttitor sit amet eu libero. Mauris aliquam gravida euismod. Ut sodales euismod urna. Donec nec urna ut odio eleifend convallis at at leo.";
	IOWR(memoria,0x000a0000,text);

	while (1){
		//printf("El resultado es: %d\n",*(contador+2));

		SW_value = *(SW_switch_ptr);
		int band = 0;
		*(contador+1)=0;
		*(contador)=4;
		*(contador)=2;
		alt_up_char_buffer_string(dev1, "Utilice una combinación de switch (SW0,SW1,SW2) para realizar consulta. ", 0,5);
		alt_up_char_buffer_string(dev1, "Utilice SW9 para mostrar la consulta realizada. ", 0,6);
		if(SW_value&512){
			char * read = IORD(memoria,0x000a0000);
			alt_up_char_buffer_clear(dev1);
			sprintf(time, "%d", *(contador+2));
			alt_up_char_buffer_string(dev1, "Mostrando consulta:", 0,1);
			alt_up_char_buffer_string(dev1, read, 0,2);
			alt_up_char_buffer_string(dev1, "En el segundo: ", 0,4);
			alt_up_char_buffer_string(dev1, time, 17,4);
			band = 1;
		}
		if(band==1)
		{	usleep(4000000);
			SW_value = *(SW_switch_ptr);
			while(SW_value&512){
				alt_up_char_buffer_string(dev1, "****************************************************************", 0,49);
				alt_up_char_buffer_string(dev1, "Regrese el switch a la posicion original para seguir consultado. ", 0,50);
				SW_value = *(SW_switch_ptr);
				printf("%d\n",SW_value);
				usleep(90000);
			}
			alt_up_char_buffer_clear(dev1);
			band =0;
		}

	}
}
