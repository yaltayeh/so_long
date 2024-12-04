#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Open the raw sound file
    int sound_fd = open("wood_cut.raw", O_RDONLY);
    if (sound_fd < 0) {
        perror("Error opening sound file");
        return 1;
    }

    // Open the audio device for playback
    int audio_fd = open("/dev/audio", O_WRONLY);
    if (audio_fd < 0) {
        perror("Error opening /dev/audio");
        close(sound_fd);
        return 1;
    }

    // Buffer for reading and writing
    unsigned char buffer[4096];
    ssize_t bytes_read;

    // Read from the file and write to the audio device
    while ((bytes_read = read(sound_fd, buffer, sizeof(buffer))) > 0) {
        if (write(audio_fd, buffer, bytes_read) != bytes_read) {
            perror("Error writing to /dev/audio");
            close(sound_fd);
            close(audio_fd);
            return 1;
        }
    }

    if (bytes_read < 0) {
        perror("Error reading sound file");
    }

    // Close the file and audio device
    close(sound_fd);
    close(audio_fd);

    return 0;
}
