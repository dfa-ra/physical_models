#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <alsa/asoundlib.h>
#include <cmath>

#define SAMPLE_RATE 16000
#define CHANNELS 1
#define BUFFER_SIZE 2048

const double l = std::numbers::pi;
const double c = 1.4;
const double rho = 0.05;
const double N = 0.8;
const double alpha = 0;
const double beta = 2;
const int n_terms = 50;
const int num_points = 1500;
const int width = 1500;
const int height = 1500;

std::vector<double> y_initial(num_points);


double calculate_volume(const short *buffer, int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += std::abs(buffer[i]);
    }
    return sum / size;
}

void apply_impact(int mouseX, int mouseY) {
    int index_x = (mouseX * num_points) / width;
    int index_y = (mouseY * num_points) / height;

    if (index_x < 0 || index_x >= num_points) return;

    for (int i = 0; i < num_points; ++i) {
        double distance = std::abs(i - index_x) / static_cast<double>(num_points);
        // std::cout << abs(width / 2 - (width - index_y)) << std::endl;
        // std::cout << distance << std::endl;
        y_initial[i] += -abs(width / 2 - (width - index_y)) * exp(-(i - width * distance) * (i - width * distance));
    }
}

void initial_shape(double l) {
    std::vector<double> y(num_points);
    for (int i = 0; i < num_points; ++i) {
        double x = l * i / (num_points - 1);
        y_initial[i] = sin(x) * cos((x+ std::numbers::pi) * (x + std::numbers::pi)) ;
    }
}

std::vector<double> compute_fourier_coefficients() {
    std::vector<double> A_n(n_terms, 0.0);
    std::vector<double> x(num_points);
    for (int i = 0; i < num_points; ++i) {
        x[i] = l * i / (num_points - 1);
    }
    for (int n = 1; n <= n_terms; ++n) {
        double k = n * M_PI / l;
        double sum = 0.0;
        for (int i = 0; i < num_points; ++i) {
            sum += y_initial[i] * sin(k * x[i]);
        }
        A_n[n - 1] = (2 / l) * sum / num_points;
    }
    return A_n;
}

std::vector<double> wave_motion(double t, const std::vector<double>& A_n, double koef) {
    std::vector<double> u(num_points, 0.0);
    std::vector<double> x(num_points);
    for (int i = 0; i < num_points; ++i) {
        x[i] = l * i / (num_points - 1);
    }
    for (int n = 1; n <= n_terms; ++n) {
        double k = n * M_PI / l;
        for (int i = 0; i < num_points; ++i) {
            u[i] += A_n[n - 1] * sin(k * x[i]) * cos(c * k * t) * exp(-N * koef);
        }
    }
    return u;
}

std::vector<double> A_n = compute_fourier_coefficients();

void zadacha_wave() {

    snd_pcm_t *capture_handle;
    snd_pcm_hw_params_t *hw_params;
    int err;

    // Открываем микрофон
    if ((err = snd_pcm_open(&capture_handle, "default", SND_PCM_STREAM_CAPTURE, 0)) < 0) {
        std::cerr << "Ошибка: " << snd_strerror(err) << std::endl;
        return;
    }

    snd_pcm_hw_params_malloc(&hw_params);
    snd_pcm_hw_params_any(capture_handle, hw_params);
    snd_pcm_hw_params_set_access(capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(capture_handle, hw_params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_rate(capture_handle, hw_params, SAMPLE_RATE, 0);
    snd_pcm_hw_params_set_channels(capture_handle, hw_params, CHANNELS);
    snd_pcm_hw_params(capture_handle, hw_params);
    snd_pcm_prepare(capture_handle);

    short buffer[BUFFER_SIZE];

    std::cout << "Говорите в микрофон..." << std::endl;


    sf::RenderWindow window(sf::VideoMode(width, height), "String Vibration");
    sf::VertexArray line(sf::LineStrip, num_points);
    double t = 0.0;
    double koef = 0.0;

    // initial_shape(l);
    // A_n = compute_fourier_coefficients();
    while (window.isOpen()) {
        err = snd_pcm_readi(capture_handle, buffer, BUFFER_SIZE);
        if (err < 0) {
            std::cerr << "Ошибка захвата аудио: " << snd_strerror(err) << std::endl;
            snd_pcm_prepare(capture_handle);
            continue;
        }


        float volume = calculate_volume(buffer, BUFFER_SIZE);
        std::cout << volume << std::endl;
        if (volume > 1000) {
            apply_impact(400, (int)volume % 5);
            A_n = compute_fourier_coefficients();
            koef = 0.0;
        }


        sf::Event event;

        std::vector<double> u = wave_motion(t, A_n, koef);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                y_initial.clear();
                y_initial.assign(u.begin(), u.end());
                std::cout << "mouse _ x " << event.mouseButton.x << std::endl;
                apply_impact(event.mouseButton.x, event.mouseButton.y);
                A_n = compute_fourier_coefficients();
                koef = 0.0;
            }

        }

        for (int i = 0; i < num_points; ++i) {
            line[i].position = sf::Vector2f(i * (width / num_points), height / 2 - u[i] * 200);
            line[i].color = sf::Color::Blue;
        }

        window.clear(sf::Color::White);
        window.draw(line);
        window.display();

        t += 0.05;
        koef += 0.05;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}