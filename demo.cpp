#include "lavi_platform.h"

#include <algorithm>
#include <array>

namespace {
    constexpr float move_speed = 1.25f;
    constexpr int virtual_key_a = 'A';
    constexpr int virtual_key_d = 'D';

    struct Vertex {
        float x;
        float y;
        float red;
        float green;
        float blue;
    };

    constexpr std::array<Vertex, 3> triangle = {{
        { 0.00f,  0.38f, 1.00f, 0.35f, 0.20f},
        {-0.34f, -0.28f, 0.20f, 0.75f, 1.00f},
        { 0.34f, -0.28f, 0.65f, 0.30f, 1.00f},
    }};

    class LaviDemo {
    public:
        LaviDemo()
        {
            api_.window.name = "Lavi C++17 Demo";
            api_.window.size = LAVI_POINT(960, 540);
        }

        LaviDemo(const LaviDemo &) = delete;
        LaviDemo &operator=(const LaviDemo &) = delete;

        void run()
        {
            lavi_init(&api_);
            lavi_printf("Lavi C++17 demo started. Move with A/D or the left stick; Escape exits.\n");

            while (!api_.quit) {
                lavi_update();
                if (api_.quit) {
                    break;
                }

                input();
                if (api_.quit) {
                    break;
                }

                render();
            }
        }

    private:
        void input()
        {
            float horizontal_input = 0.0f;
            const float delta_seconds =
                std::clamp(api_.time.delta_sec, 0.0f, 0.1f);

            if (api_.keys[virtual_key_a].is_down) {
                horizontal_input -= 1.0f;
            }
            if (api_.keys[virtual_key_d].is_down) {
                horizontal_input += 1.0f;
            }
            if (api_.gamepad.connected) {
                horizontal_input += api_.gamepad.lthumb_stick.axis.x;
            }

            position_x_ = std::clamp(
                position_x_ + horizontal_input * move_speed * delta_seconds,
                -0.75f,
                0.75f);
            rotation_degrees_ += 45.0f * delta_seconds;

            if (api_.keys[LAVI_VK_ESC].is_pressed) {
                api_.quit = LAVI_TRUE;
            }
        }

        void render() 
        {
            const int width = std::max(api_.window.size.x, 1);
            const int height = std::max(api_.window.size.y, 1);
            const float aspect = static_cast<float>(width) /
                                 static_cast<float>(height);

            glViewport(0, 0, width, height);
            glClearColor(0.035f, 0.045f, 0.075f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-aspect, aspect, -1.0, 1.0, -1.0, 1.0);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(position_x_, 0.0f, 0.0f);
            glRotatef(rotation_degrees_, 0.0f, 0.0f, 1.0f);

            glBegin(GL_TRIANGLES);
            for (const Vertex &vertex : triangle) {
                glColor3f(vertex.red, vertex.green, vertex.blue);
                glVertex2f(vertex.x, vertex.y);
            }
            glEnd();
        }

        lavi_api api_{};
        float position_x_ = 0.0f;
        float rotation_degrees_ = 0.0f;
    };
} 

void
lavi_main(int argc, char **argv)
{
    LaviDemo demo;
    demo.run();
}
