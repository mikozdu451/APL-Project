#pragma once
#include <fstream>
#include <vector>
#include <stdexcept>
#include <thread>
#include <vector>
#include <mutex>
#include <iostream>
std::mutex mtx_grey;
std::mutex mtx_sepia;

#pragma pack(push, 1)

extern "C" float _stdcall MyProc3(double R, double G, double B);

struct BMPFileHeader {
    uint16_t file_type{ 0x4D42 }; // File type always BM which is 0x4D42 (stored as hex uint16_t in little endian)
    uint32_t file_size{ 0 }; // Size of the file (in bytes)
    uint16_t reserved1{ 0 }; // Reserved, always 0
    uint16_t reserved2{ 0 }; // Reserved, always 0
    uint32_t offset_data{ 0 }; // Start position of pixel data (bytes from the beginning of the file)
};

struct BMPInfoHeader {
    uint32_t size{ 0 }; // Size of this header (in bytes)
    int32_t width{ 0 }; // width of bitmap in pixels
    int32_t height{ 0 }; // width of bitmap in pixels
    // (if positive, bottom-up, with origin in lower left corner)
    // (if negative, top-down, with origin in upper left corner)
    uint16_t planes{ 1 }; // No. of planes for the target device, this is always 1
    uint16_t bit_count{ 0 }; // No. of bits per pixel
    uint32_t compression{ 0 }; // 0 or 3 - uncompressed. THIS PROGRAM CONSIDERS ONLY UNCOMPRESSED BMP images
    uint32_t size_image{ 0 }; // 0 - for uncompressed images
    int32_t x_pixels_per_meter{ 0 };
    int32_t y_pixels_per_meter{ 0 };
    uint32_t colors_used{ 0 }; // No. color indexes in the color table. Use 0 for the max number of colors allowed by bit_count
    uint32_t colors_important{ 0 }; // No. of colors used for displaying the bitmap. If 0 all colors are required
};

struct BMPColorHeader {
    uint32_t red_mask{ 0x00ff0000 }; // Bit mask for the red channel
    uint32_t green_mask{ 0x0000ff00 }; // Bit mask for the green channel
    uint32_t blue_mask{ 0x000000ff }; // Bit mask for the blue channel
    uint32_t alpha_mask{ 0xff000000 }; // Bit mask for the alpha channel
    uint32_t color_space_type{ 0x73524742 }; // Default "sRGB" (0x73524742)
    uint32_t unused[16]{ 0 }; // Unused data for sRGB color space
};
#pragma pack(pop)

struct BMP {
    BMPFileHeader file_header;
    BMPInfoHeader bmp_info_header;
    BMPColorHeader bmp_color_header;
    std::vector<uint8_t> data;

    BMP(const char* fname) {
        read(fname);
    }

    void read(const char* fname) {
        std::ifstream inp{ fname, std::ios_base::binary };
        if (inp) {
            inp.read((char*)&file_header, sizeof(file_header));
            if (file_header.file_type != 0x4D42) {
                throw std::runtime_error("Error! Unrecognized file format.");
            }
            inp.read((char*)&bmp_info_header, sizeof(bmp_info_header));

            // The BMPColorHeader is used only for transparent images
            if (bmp_info_header.bit_count == 32) {
                // Check if the file has bit mask color information
                if (bmp_info_header.size >= (sizeof(BMPInfoHeader) + sizeof(BMPColorHeader))) {
                    inp.read((char*)&bmp_color_header, sizeof(bmp_color_header));
                    // Check if the pixel data is stored as BGRA and if the color space type is sRGB
                    check_color_header(bmp_color_header);
                }
                else {
                    std::cerr << "Error! The file \"" << fname << "\" does not seem to contain bit mask information\n";
                    throw std::runtime_error("Error! Unrecognized file format.");
                }
            }

            // Jump to the pixel data location
            inp.seekg(file_header.offset_data, inp.beg);

            // Adjust the header fields for output.
            // Some editors will put extra info in the image file, we only save the headers and the data.
            if (bmp_info_header.bit_count == 32) {
                bmp_info_header.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
                file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
            }
            else {
                bmp_info_header.size = sizeof(BMPInfoHeader);
                file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
            }
            file_header.file_size = file_header.offset_data;

            if (bmp_info_header.height < 0) {
                throw std::runtime_error("The program can treat only BMP images with the origin in the bottom left corner!");
            }

            data.resize(bmp_info_header.width * bmp_info_header.height * bmp_info_header.bit_count / 8);

            // Here we check if we need to take into account row padding
            if (bmp_info_header.width % 4 == 0) {
                inp.read((char*)data.data(), data.size());
                file_header.file_size += data.size();
            }
            else {
                row_stride = bmp_info_header.width * bmp_info_header.bit_count / 8;
                uint32_t new_stride = make_stride_aligned(4);
                std::vector<uint8_t> padding_row(new_stride - row_stride);

                for (int y = 0; y < bmp_info_header.height; ++y) {
                    inp.read((char*)(data.data() + row_stride * y), row_stride);
                    inp.read((char*)padding_row.data(), padding_row.size());
                }
                file_header.file_size += data.size() + bmp_info_header.height * padding_row.size();
            }
        }
        else {
            throw std::runtime_error("Unable to open the input image file.");
        }
    }

    BMP(int32_t width, int32_t height, bool has_alpha = true) {
        if (width <= 0 || height <= 0) {
            throw std::runtime_error("The image width and height must be positive numbers.");
        }

        bmp_info_header.width = width;
        bmp_info_header.height = height;
        if (has_alpha) {
            bmp_info_header.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
            file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);

            bmp_info_header.bit_count = 32;
            bmp_info_header.compression = 3;
            row_stride = width * 4;
            data.resize(row_stride * height);
            file_header.file_size = file_header.offset_data + data.size();
        }
        else {
            bmp_info_header.size = sizeof(BMPInfoHeader);
            file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

            bmp_info_header.bit_count = 24;
            bmp_info_header.compression = 0;
            row_stride = width * 3;
            data.resize(row_stride * height);

            uint32_t new_stride = make_stride_aligned(4);
            file_header.file_size = file_header.offset_data + data.size() + bmp_info_header.height * (new_stride - row_stride);
        }
    }

    void write(const char* fname) {
        std::ofstream of{ fname, std::ios_base::binary };
        if (of) {
            if (bmp_info_header.bit_count == 32) {
                write_headers_and_data(of);
            }
            else if (bmp_info_header.bit_count == 24) {
                if (bmp_info_header.width % 4 == 0) {
                    write_headers_and_data(of);
                }
                else {
                    uint32_t new_stride = make_stride_aligned(4);
                    std::vector<uint8_t> padding_row(new_stride - row_stride);

                    write_headers(of);

                    for (int y = 0; y < bmp_info_header.height; ++y) {
                        of.write((const char*)(data.data() + row_stride * y), row_stride);
                        of.write((const char*)padding_row.data(), padding_row.size());
                    }
                }
            }
            else {
                throw std::runtime_error("The program can treat only 24 or 32 bits per pixel BMP files");
            }
        }
        else {
            throw std::runtime_error("Unable to open the output image file.");
        }
    }

    void grayscale() {
        uint32_t num_threads = bmp_info_header.height;
        global_row_greyscale_threads = 0;

        time_t start, end;
        time(&start);
        for (uint32_t i = 0; i < num_threads; i++) {
            some_threads.push_back(std::thread(&BMP::transform_row_to_greyscale, this));
        }
        for (auto& t : some_threads) {
            t.join();
        }
        some_threads.clear();
        time(&end);
        std::cout << difftime(end, start) << " seconds (rgb to grescale - HEIGHT: " << bmp_info_header.height << " threads, 1 per row, WIDTH: " << bmp_info_header.width << ")" << std::endl;
    }

    void sepia() {
        uint32_t num_threads = bmp_info_header.height;
        global_row_sepia_threads = 0;

        time_t start, end;
        time(&start);
        for (uint32_t i = 0; i < num_threads; i++) {
            some_threads.push_back(std::thread(&BMP::transform_row_to_sepia, this));
        }
        for (auto& t : some_threads) {
            t.join();
        }
        some_threads.clear();
        time(&end);
        std::cout << difftime(end, start) << " seconds (rgb to sepia - HEIGHT: " << bmp_info_header.height << " threads, 1 per row, WIDTH: " << bmp_info_header.width << ")" << std::endl;
    }

    void transform_row_to_greyscale() {
        uint32_t channels = bmp_info_header.bit_count / 8;
        uint32_t grey{ 0 };
        float A = 0.0, R = 0.0, G = 0.0, B = 0.0;
        float temp_grey;
        mtx_grey.lock();
        for (uint32_t column = 0; column < bmp_info_header.width; column++) {
            R = float(data[channels * (global_row_greyscale_threads * bmp_info_header.width + column) + 0]);
            G = float(data[channels * (global_row_greyscale_threads * bmp_info_header.width + column) + 1]);
            B = float(data[channels * (global_row_greyscale_threads * bmp_info_header.width + column) + 2]);
            std::cout << "R: " << R << " G: " << G << " B: " << B << std::endl;
            temp_grey = MyProc3(float(R), float(G), float(B));
            std::cout << "temp_grey: " << temp_grey << std::endl;
            grey = temp_grey;
            std::cout << "grey: " << grey << std::endl;
            data[channels * (global_row_greyscale_threads * bmp_info_header.width + column) + 0] = grey;
            data[channels * (global_row_greyscale_threads * bmp_info_header.width + column) + 1] = grey;
            data[channels * (global_row_greyscale_threads * bmp_info_header.width + column) + 2] = grey;
        }
        global_row_greyscale_threads += 1;
        mtx_grey.unlock();
    }

    void transform_row_to_sepia() {
        uint32_t channels = bmp_info_header.bit_count / 8;
        uint32_t A{ 0 }, R{ 0 }, G{ 0 }, B{ 0 }, grey{ 0 };
        uint32_t tr{ 0 }, tg{ 0 }, tb{ 0 };
        mtx_sepia.lock();
        for (uint32_t column = 0; column < bmp_info_header.width; column++) {
            R = data[channels * (global_row_sepia_threads * bmp_info_header.width + column) + 0];
            G = data[channels * (global_row_sepia_threads * bmp_info_header.width + column) + 1];
            B = data[channels * (global_row_sepia_threads * bmp_info_header.width + column) + 2];

            tr = 0.393 * R + 0.769 * G + 0.189 * B;
            tg = 0.349 * R + 0.686 * G + 0.168 * B;
            tb = 0.272 * R + 0.534 * G + 0.131 * B;

            if (tr > 255) R = 255;
            else R = tr;
            if (tg > 255) G = 255;
            else G = tg;
            if (tb > 255) B = 255;
            else B = tb;

            data[channels * (global_row_sepia_threads * bmp_info_header.width + column) + 0] = R;
            data[channels * (global_row_sepia_threads * bmp_info_header.width + column) + 1] = G;
            data[channels * (global_row_sepia_threads * bmp_info_header.width + column) + 2] = B;
        }
        global_row_sepia_threads += 1;
        mtx_sepia.unlock();
    }

    void fill_region(uint32_t x0, uint32_t y0, uint32_t w, uint32_t h, uint8_t B, uint8_t G, uint8_t R, uint8_t A) {
        if (x0 + w > (uint32_t)bmp_info_header.width || y0 + h > (uint32_t)bmp_info_header.height) {
            throw std::runtime_error("The region does not fit in the image!");
        }

        uint32_t channels = bmp_info_header.bit_count / 8;
        for (uint32_t y = y0; y < y0 + h; ++y) {
            for (uint32_t x = x0; x < x0 + w; ++x) {
                data[channels * (y * bmp_info_header.width + x) + 0] = B;
                data[channels * (y * bmp_info_header.width + x) + 1] = G;
                data[channels * (y * bmp_info_header.width + x) + 2] = R;
                if (channels == 4) {
                    data[channels * (y * bmp_info_header.width + x) + 3] = A;
                }
            }
        }
    }

private:
    uint32_t row_stride{ 0 };
    uint32_t global_row_greyscale_threads{ 0 };
    uint32_t global_row_sepia_threads{ 0 };
    std::vector<std::thread> some_threads;

    void write_headers(std::ofstream& of) {
        of.write((const char*)&file_header, sizeof(file_header));
        of.write((const char*)&bmp_info_header, sizeof(bmp_info_header));
        if (bmp_info_header.bit_count == 32) {
            of.write((const char*)&bmp_color_header, sizeof(bmp_color_header));
        }
    }

    void write_headers_and_data(std::ofstream& of) {
        write_headers(of);
        of.write((const char*)data.data(), data.size());
    }

    // Add 1 to the row_stride until it is divisible with align_stride

    uint32_t make_stride_aligned(uint32_t align_stride) {
        uint32_t new_stride = row_stride;
        while (new_stride % align_stride != 0) {
            new_stride++;
        }
        return new_stride;
    }

    // Check if the pixel data is stored as BGRA and if the color space type is sRGB

    void check_color_header(BMPColorHeader& bmp_color_header) {
        BMPColorHeader expected_color_header;
        if (expected_color_header.red_mask != bmp_color_header.red_mask ||
            expected_color_header.blue_mask != bmp_color_header.blue_mask ||
            expected_color_header.green_mask != bmp_color_header.green_mask ||
            expected_color_header.alpha_mask != bmp_color_header.alpha_mask) {
            throw std::runtime_error("Unexpected color mask format! The program expects the pixel data to be in the BGRA format");
        }
        if (expected_color_header.color_space_type != bmp_color_header.color_space_type) {
            throw std::runtime_error("Unexpected color space type! The program expects sRGB values");
        }
    }
};