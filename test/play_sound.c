#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <alsa/asoundlib.h>

#define PCM_DEVICE "default"  // Change to "hw:0,0" if necessary for your device

int main() {
    snd_pcm_t *pcm_handle;
    snd_pcm_hw_params_t *params;
    unsigned int rate = 44100;        // Sample rate (44.1 kHz)
    int channels = 2;                 // Stereo
    int format = SND_PCM_FORMAT_S16_LE; // 16-bit little-endian PCM
    int dir;
    snd_pcm_uframes_t frames;
    FILE *audio_file;
    char buffer[1024];                // Buffer for raw audio data
    size_t bytes_read;

    // Open the PCM device for playback
    if (snd_pcm_open(&pcm_handle, PCM_DEVICE, SND_PCM_STREAM_PLAYBACK, 0) < 0) {
        perror("Error opening PCM device");
        return 1;
    }

    // Allocate memory for hardware parameters
    snd_pcm_hw_params_malloc(&params);

    // Set default values for hardware parameters
    snd_pcm_hw_params_any(pcm_handle, params);

    // Set the sample format
    snd_pcm_hw_params_set_format(pcm_handle, params, format);

    // Set the number of channels (stereo)
    snd_pcm_hw_params_set_channels(pcm_handle, params, channels);

    // Set the sample rate
    snd_pcm_hw_params_set_rate_near(pcm_handle, params, &rate, &dir);

    // Apply the hardware parameters to the PCM device
    if (snd_pcm_hw_params(pcm_handle, params) < 0) {
        perror("Error setting hardware parameters");
        snd_pcm_close(pcm_handle);
        return 1;
    }

    // Prepare the PCM device for playback
    if (snd_pcm_prepare(pcm_handle) < 0) {
        perror("Error preparing PCM device");
        snd_pcm_close(pcm_handle);
        return 1;
    }

    // Open the raw audio file
    audio_file = fopen("output.raw", "rb");
    if (!audio_file) {
        perror("Error opening raw audio file");
        snd_pcm_close(pcm_handle);
        return 1;
    }

    // Read and write the raw audio data to the PCM device
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), audio_file)) > 0) {
        size_t frames_to_write = bytes_read / 4;  // 4 bytes per frame (16-bit stereo)
        printf("Writing %zu frames\n", frames_to_write);

        if (snd_pcm_writei(pcm_handle, buffer, frames_to_write) < 0) {
            perror("Error writing to PCM device");
            fclose(audio_file);
            snd_pcm_close(pcm_handle);
            return 1;
        }
    }

    // Clean up and close everything
    fclose(audio_file);
    snd_pcm_close(pcm_handle);

    return 0;
}
