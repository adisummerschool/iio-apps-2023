#include <stdio.h>
#include <iio.h>

#define URI "ip:10.76.84.153"

int main() {

	int n,m,p,ind;
	unsigned int major;
	unsigned int minor;
	char git_tag[8];
	const char *description;
	const char *ctx_name;
	const char *ctx_val;
	const char *dev_name;
	const char *dev_attr;
	const char *chan_id;
	const char *chan_attr;
	struct iio_context *ctx;
	struct iio_device *dev;
	struct iio_channel *channel;

	iio_library_get_version(&major, &minor, git_tag);

	printf("libiio version: %d.%d - %s \n", major,minor,git_tag);

	ctx = iio_create_context_from_uri(URI);
	if(ctx == NULL)
	{
		printf("Error! Context not available! Exiting the program.\n");
		return 0;
	}
	description = iio_context_get_description(ctx);
	printf("Description: %s\n" , description);
	n=iio_context_get_attrs_count(ctx);
	printf("Context count: %d\n",n);
	for(int i=0; i<n; i++)
	{
		iio_context_get_attr(ctx,i,&ctx_name,&ctx_val); 
		printf("ctx attr %d: %s - %s\n" ,i, ctx_name, ctx_val);
	}

	n=iio_context_get_devices_count(ctx);
	printf("\nDevices count: %d\n",n);

	dev=iio_context_find_device(ctx,"ad5592r_s");
	dev_name=iio_device_get_name(dev);
	m=iio_device_get_attrs_count(dev);
	for(int j=0; j<m; j++)
	{
		dev_attr=iio_device_get_attr(dev,j);
		printf("dev %s attr %s\n" ,dev_name, dev_attr);
	}
	p=iio_device_get_channels_count(dev);
	printf("\nChannel count: %d\n",p);
		
	for(int k=0; k<p; k++)
	{
		channel=iio_device_get_channel(dev,k);
		chan_id=iio_channel_get_id(channel);
		chan_attr=iio_channel_get_attr(channel,0);
		printf("channel %s attr %s\n" ,chan_id, chan_attr);
	}
	printf("\n");

	
	iio_context_destroy(ctx);

	return 0;
}
