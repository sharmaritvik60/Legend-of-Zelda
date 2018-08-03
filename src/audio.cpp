#include <ao/ao.h>
#include <mpg123.h>

ao_device *dev;
unsigned char *buffer;
mpg123_handle *mpg_handle;

void audio_init()
{
	ao_sample_format format;
	int error, encoding, channels, driver;
	long int rate;
	ao_initialize();
	driver = ao_default_driver_id();
	mpg123_init();
	mpg_handle = mpg123_new(NULL, &error);
	buffer = (unsigned char*) malloc(32 * sizeof(unsigned char));

	mpg123_open(mpg_handle, "background_score.mp3");
	mpg123_getformat(mpg_handle, &rate, &channels, &encoding);

	format.matrix = 0;
	format.byte_format = AO_FMT_NATIVE;
	format.bits = 8*mpg123_encsize(encoding);
	format.rate = rate;
	format.channels = channels;
	dev = ao_open_live(driver, &format, NULL);
	return;
}

void audio_play()
{
	size_t done;
	if(mpg123_read(mpg_handle, buffer, 32, &done) == MPG123_OK)
		ao_play(dev, (char*) buffer, done);
	else
		mpg123_seek(mpg_handle, 0, SEEK_SET);
	return;
}

void audio_close()
{
	free(buffer);
	ao_close(dev);
	mpg123_close(mpg_handle);
	mpg123_delete(mpg_handle);
	mpg123_exit();
	ao_shutdown();
	return;
}
