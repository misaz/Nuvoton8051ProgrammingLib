#include "Nuvoton8051PlatformSpecific.h"

static int __isInitialized = 0;

static void __exitIfPinIsExported(const char* pinFile) {
	struct stat dummy;
	int retval = stat(pinFile, &dummy);

	if (retval == 0) {
		printf("%s gpio pin is already exported.\n", pinFile);
		exit(1);
	} else {
		int err = errno;

		if (err != ENOENT) {
			printf("I/O error while calling stat agains %s gpio pin. Error %d (%s)\n", pinFile, err, strerror(err));
			exit(1);
		}
	}
}

static void __tryWriteFile(const char* file, const char* content) {
	int fd = open(file, O_WRONLY);
	if (fd < 1) {
		int err = errno;
		printf("I/O error while opening %s file. Error %d (%s)\n", file, err, strerror(err));
		Nuvoton8051_RaspberryPiUninit();
		exit(1); 
		return;
	}

	size_t len = strlen(content);

	if (write(fd, content, len) != len) {
		int err = errno;
		printf("I/O error while writing to %s file. Error %d (%s)\n", file, err, strerror(err));
		Nuvoton8051_RaspberryPiUninit();
		exit(1);
		return;
	}

	if (close(fd) != 0) {
		int err = errno;
		printf("I/O error while closing %s file. Error %d (%s)\n", file, err, strerror(err));
		Nuvoton8051_RaspberryPiUninit();
		exit(1);
		return;
	}
}

static char __tryReadCharFromFile(const char* file) {
	int fd = open(file, O_RDONLY);
	if (fd < 1) {
		int err = errno;
		printf("I/O error while opening %s file. Error %d (%s)\n", file, err, strerror(err));
		Nuvoton8051_RaspberryPiUninit();
		exit(1);
		return '\0';
	}

	char output;
	if (read(fd, &output, 1) != 1) {
		int err = errno;
		printf("I/O error while reading byte from %s file. Error %d (%s)\n", file, err, strerror(err));
		Nuvoton8051_RaspberryPiUninit();
		exit(1);
		return '\0';
	}

	if (close(fd) != 0) {
		int err = errno;
		printf("I/O error while closing %s file. Error %d (%s)\n", file, err, strerror(err));
		Nuvoton8051_RaspberryPiUninit();
		exit(1);
		return '\0';
	}

	return output;
}

static void __tryExportPin(const char* pinNumber) {
	__tryWriteFile("/sys/class/gpio/export", pinNumber);
}

static void __tryUnexportPin(const char* pinNumber) {
	__tryWriteFile("/sys/class/gpio/unexport", pinNumber);
}

static void __trySetDirection(const char* directionFile, const char* direction) {
	__tryWriteFile(directionFile, direction);
}

static void __trySetValue(const char* valueFile, const char* value) {
	__tryWriteFile(valueFile, value);
}

static uint32_t __tryGetValue(const char* valueFile) {
	return __tryReadCharFromFile(valueFile) == '1';
}

void Nuvoton8051_GpioInit() {
	__exitIfPinIsExported(NU8051_RST_PIN_FILE);
	__exitIfPinIsExported(NU8051_CLK_PIN_FILE);
	__exitIfPinIsExported(NU8051_DAT_PIN_FILE);

	__tryExportPin(NU8051_RST_PIN_NUM);
	__tryExportPin(NU8051_CLK_PIN_NUM);
	__tryExportPin(NU8051_DAT_PIN_NUM);
	
	__isInitialized = 1;
	
	__trySetDirection(NU8051_RST_PIN_DIRECTION_FILE, "out");
	__trySetDirection(NU8051_CLK_PIN_DIRECTION_FILE, "out");
	__trySetDirection(NU8051_DAT_PIN_DIRECTION_FILE, "out");
}

void Nuvoton8051_RaspberryPiUnexportPins() {
	__tryUnexportPin(NU8051_RST_PIN_NUM);
	__tryUnexportPin(NU8051_CLK_PIN_NUM);
	__tryUnexportPin(NU8051_DAT_PIN_NUM);

	__isInitialized = 0;
}

void Nuvoton8051_RaspberryPiUninit() {
	if (__isInitialized) {
		Nuvoton8051_RaspberryPiUnexportPins();
	}
}

void Nuvoton8051_DelayUs(uint32_t periodUs) {
	usleep(periodUs * 10);
}

void Nuvoton8051_GpioSetRstState(uint32_t level) {
	__trySetValue(NU8051_RST_PIN_VALUE_FILE, level ? "1" : "0");
}

void Nuvoton8051_GpioSetClkState(uint32_t level) {
	__trySetValue(NU8051_CLK_PIN_VALUE_FILE, level ? "1" : "0");
}

void Nuvoton8051_GpioSetDatState(uint32_t level) {
	__trySetValue(NU8051_DAT_PIN_VALUE_FILE, level ? "1" : "0");
}

uint32_t Nuvoton8051_GpioGetDatState() {
	return __tryGetValue(NU8051_DAT_PIN_VALUE_FILE);
}

void Nuvoton8051_GpioSetDatAsInput() {
	__trySetDirection(NU8051_DAT_PIN_DIRECTION_FILE, "in");
}

void Nuvoton8051_GpioSetDatAsOutput() {
	__trySetDirection(NU8051_DAT_PIN_DIRECTION_FILE, "out");
}
