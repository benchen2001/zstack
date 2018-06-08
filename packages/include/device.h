#ifndef DEVICE_H
#define DEVICE_H

struct device {
	char *name;
};

struct device * device_find ( char *name );

int device_info ( struct device *dev );

int device_signal ( struct device *dev, void signal );

int device_config ( struct device *dev, void *param);

int device_power_control ( struct device *dev, int status );

#endif

