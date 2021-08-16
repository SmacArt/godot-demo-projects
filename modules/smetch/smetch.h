/* smetch.h */

#ifndef SMETCH_H
#define SMETCH_H

#include "core/math/color.h"
#include "core/os/os.h"
#include "scene/gui/texture_rect.h"
#include "scene/main/viewport.h"
#include "smetch_properties.h"
#include "core/math/random_number_generator.h"
#include "core/io/file_access.h"
#include "scene/gui/file_dialog.h"

class Smetch : public TextureRect {
	GDCLASS(Smetch, TextureRect);

protected:
	static void _bind_methods();

public:
	enum Constants {
		RGB,
		HSB,
		HSL,
		CORNER,
		CORNERS,
		RADIUS,
		CENTER,
    CURSOR_HIDDEN,
    CURSOR_ARROW,
    GIMP
};

  void set_properties(const Ref<SmetchProperties> &properties);
  Ref<SmetchProperties> get_properties() const;

	void background(float value1, float value2, float value3);
	void color_mode(int mode, float value1, float value2, float value3, float value4);
	void create_canvas(double x, double y);
	void create(double x, double y);
	void resize_canvas(double x, double y);
	void resize(double x, double y);
	void fill(float value1, float value2, float value3);
	Color prime_color(Color color, float value1, float value2, float value3, float value4);
	void fill_with_color(Color color);
	void rect(float x, float y, float w, float h);
	void no_cursor();
	void no_stroke();
  void continuous_drawing(bool is_continuous);
	void rect_mode(int mode);
	String save_canvas(String file_name);
  String save_palette(String file_name, int format, double columns);

	Vector2 get_mouse_position();
  void update_cursor();
  Color get_current_color();
  Color lerp_color(Color c1, Color c2, float amt);
  double map(double n, double start1, double stop1, double start2, double stop2);
  float fmap(float n, float start1, float stop1, float start2, float stop2);
  double constrain(double n, double low, double high);
  float fconstrain(float n, float low, float high);
  double min(double n1, double n2);
  double max(double n1, double n2);
  double random(double from, double to);
  float frandom(float from, float to);

  void add_color_to_palette(Color color);
  void clear_palette();

  void open_file_dialog();
  Ref<Image> load_image(String path);
  Ref<ImageTexture>load_image_texture(String path);

  void _on_FileDialog_file_selected(const String path);

  void _ready();
  void _process(float delta);

	Smetch();
  ~Smetch();

private:
	Color apply_color(float value1, float value2, float value3, float value4, Color to_color);
  void mouse_entered();
  void mouse_exited();

  Ref<SmetchProperties> properties;

	Color fill_color;
	Color background_color;
	Rect2 background_rect;
	CanvasTexture *canvas_texture;
  RandomNumberGenerator *random_number_generator;
  FileDialog *file_dialog = nullptr;

	int clr_mode = RGB;
	int color_maxes[3][4] = {
		{ 255, 255, 255, 255 }, // RGB
		{ 360, 100, 100, 1 }, // HSB
		{ 360, 100, 100, 1 } // HSL
	};
	int maxes[4];
  bool renderer_no_stroke;
  bool is_continuous_drawing = true;
	int rct_mode = CORNER;
  int cursor_mode = CURSOR_ARROW;
  Input::MouseMode parent_mouse_mode;

  PackedColorArray palette_colors;
};

#endif // SMETCH_H
