#include <iostream>
#include <fstream>
#include <cstring>
#include "BMP.h"

using namespace std;

int N = 3,
	horiz_camera_rez = 640,
	vert_camera_rez = 480
;
float fov = 46.6f,
	  over_compensation_precent = 0.93681f,
	  camera_vertical_offset = 0.0f ,
	  horizontal_edge_length = 42.0f,
	  vertical_edge_length = 30.0f,
	  mirror_size= 3.2f,
      max_distance_reflection  = 44.35f,
	  additional_distance = 17.35f
;
float mirror_ratio = (3 * mirror_size) / horizontal_edge_length;

struct rectangle {
	int horiz_pixel = 0;
	int vert_pixel = 0;
};

void set_pixel_size(rectangle &rect, float z) {
	rect.horiz_pixel = (additional_distance * horiz_camera_rez) / (max_distance_reflection - z)* over_compensation_precent;
	rect.vert_pixel = (additional_distance * horiz_camera_rez * mirror_ratio) / (max_distance_reflection - z);
}

void int_to_char(char *int_chr, int nr) {
	if (nr >= 10) {
		int_chr[0] = (nr / 10) + '0';
		nr = nr % 10;
		int_chr[1] = nr + '0';
		int_chr[2] = 0;
	}
	else{
		int_chr[0] = nr  + '0';
		int_chr[1] = 0;
	}

}

int main() {
	rectangle center;
	for (int frame = 0; frame <= 50; frame++) {
		char frame_char[4];
		char original_path[96] = "C:/Users/matei/Documents/Google Drive/Tabla smart - Escreo/Smart-Board-Code/Data/C1_feed/";
		char copy_path[112] = "C:/Users/matei/Documents/Google Drive/Tabla smart - Escreo/Smart-Board-Code/Post-Procesor-Data-Cache/";
		int_to_char(frame_char, frame);
		strcat_s(copy_path, frame_char);
		strcat_s(copy_path, "Copy.bmp");
		strcat_s(original_path, frame_char);
		strcat_s(original_path, ".bmp");
		set_pixel_size(center, 27.0f * ((float)frame / (float)50));
		cout << original_path << "\n";
		bitmap bmp{ original_path };
		cout << center.horiz_pixel << " " << center.vert_pixel;
		for (int y = 0; y < center.vert_pixel; ++y) {
			for (int x = 0; x < center.horiz_pixel; ++x) {
				rgb32 pixel = { 0x0, 0, 0xff, 0 };
				bmp.setPixel(&pixel, x + (horiz_camera_rez - center.horiz_pixel) / (float)2, y + (vert_camera_rez - camera_vertical_offset - center.vert_pixel) / (float)2);
			}
		}
		bmp.save(copy_path);
	}
}