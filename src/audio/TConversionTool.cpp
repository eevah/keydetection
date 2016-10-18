#include "TConversionTool.h"


const std::vector<int> TConversionTool::exp_lut1_tconv = {0,0,1,1,2,2,2,2,3,3,3,3,3,3,3,3, 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4, 5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5, 5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5, 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6, 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6, 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6, 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7};
const std::vector<short> TConversionTool::seg_end_tconv = {0xFF, 0x1FF, 0x3FF, 0x7FF, 0xFFF, 0x1FFF, 0x3FFF, 0x7FFF};

void TConversionTool::convertSign8(std::vector<char> &buffer, int byteOffset, int sampleCount)
{
	sampleCount += byteOffset;
	for (int i = byteOffset; i < sampleCount; i++)
	{
		buffer[i] += 128;
	}
}

void TConversionTool::swapOrder16(std::vector<char> &buffer, int byteOffset, int sampleCount)
{
	int byteMax = sampleCount*2 + byteOffset - 1;
	int i = byteOffset;
	while (i < byteMax)
	{
		char h = buffer[i];
		buffer[i] = buffer[++i];
		buffer[i++] = h;
	}
}

void TConversionTool::swapOrder24(std::vector<char> &buffer, int byteOffset, int sampleCount)
{
	int byteMax = sampleCount*3 + byteOffset - 2;
	int i = byteOffset;
	while (i < byteMax)
	{
		char h = buffer[i];
		buffer[i] = buffer[++i + 1];
		buffer[++i] = h;
		i++;
	}
}

///////////////// conversion functions for byte arrays ////////////////////////////


/**
 * Converts 2 bytes to a signed sample of type <code>short</code>.
 * <p> This is a reference function.
 */
short bytesToShort16(char highByte, char lowByte) {
	return (short) ((highByte<<8) | (lowByte & 0xFF));
}

/**
 * Converts 2 successive bytes starting at <code>byteOffset</code> in
 * <code>buffer</code> to a signed sample of type <code>short</code>.
 * <p>
 * For little endian, buffer[byteOffset] is interpreted as low byte,
 * whereas it is interpreted as high byte in big endian.
 * <p> This is a reference function.
 */
short bytesToShort16(std::vector<char> &buffer, int byteOffset, bool bigEndian) {
	return bigEndian?
		   ((short) ((buffer[byteOffset]<<8) | (buffer[byteOffset+1] & 0xFF))):
		   ((short) ((buffer[byteOffset+1]<<8) | (buffer[byteOffset] & 0xFF)));
}

/**
 * Converts 2 bytes to a signed integer sample with 16bit range.
 * <p> This is a reference function.
 */
int bytesToInt16(char highByte, char lowByte) {
	return (highByte<<8) | (lowByte & 0xFF);
}

/**
 * Converts 2 successive bytes starting at <code>byteOffset</code> in
 * <code>buffer</code> to a signed integer sample with 16bit range.
 * <p>
 * For little endian, buffer[byteOffset] is interpreted as low byte,
 * whereas it is interpreted as high byte in big endian.
 * <p> This is a reference function.
 */
int bytesToInt16(std::vector<char> &buffer, int byteOffset, bool bigEndian) {
	return bigEndian?
		   ((buffer[byteOffset]<<8) | (buffer[byteOffset+1] & 0xFF)):
		   ((buffer[byteOffset+1]<<8) | (buffer[byteOffset] & 0xFF));
}

/**
 * Converts 3 successive bytes starting at <code>byteOffset</code> in
 * <code>buffer</code> to a signed integer sample with 24bit range.
 * <p>
 * For little endian, buffer[byteOffset] is interpreted as lowest byte,
 * whereas it is interpreted as highest byte in big endian.
 * <p> This is a reference function.
 */
int bytesToInt24(std::vector<char> &buffer, int byteOffset, bool bigEndian) {
	return bigEndian?
		   ((buffer[byteOffset]<<16)             // let Java handle sign-bit
			| ((buffer[byteOffset+1] & 0xFF)<<8) // inhibit sign-bit handling
			| (buffer[byteOffset+2] & 0xFF)):
		   ((buffer[byteOffset+2]<<16)           // let Java handle sign-bit
			| ((buffer[byteOffset+1] & 0xFF)<<8) // inhibit sign-bit handling
			| (buffer[byteOffset] & 0xFF));
}

/**
 * Converts a 4 successive bytes starting at <code>byteOffset</code> in
 * <code>buffer</code> to a signed 32bit integer sample.
 * <p>
 * For little endian, buffer[byteOffset] is interpreted as lowest byte,
 * whereas it is interpreted as highest byte in big endian.
 * <p> This is a reference function.
 */
int bytesToInt32(std::vector<char> &buffer, int byteOffset, bool bigEndian) {
	return bigEndian?
		   ((buffer[byteOffset]<<24)              // let Java handle sign-bit
			| ((buffer[byteOffset+1] & 0xFF)<<16) // inhibit sign-bit handling
			| ((buffer[byteOffset+2] & 0xFF)<<8)  // inhibit sign-bit handling
			| (buffer[byteOffset+3] & 0xFF)):
		   ((buffer[byteOffset+3]<<24)            // let Java handle sign-bit
			| ((buffer[byteOffset+2] & 0xFF)<<16) // inhibit sign-bit handling
			| ((buffer[byteOffset+1] & 0xFF)<<8)  // inhibit sign-bit handling
			| (buffer[byteOffset] & 0xFF));
}


void TConversionTool::swapOrder32(std::vector<char> &buffer, int byteOffset, int sampleCount)
{
	int byteMax = sampleCount*4 + byteOffset - 3;
	int i = byteOffset;
	while (i < byteMax)
	{
		char h = buffer[i];
		buffer[i] = buffer[i + 3];
		buffer[i + 3] = h;
		i++;
		h = buffer[i];
		buffer[i] = buffer[++i];
		buffer[i++] = h;
		i++;
	}
}

void TConversionTool::convertSign8(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount)
{
	while (sampleCount > 0)
	{
		outBuffer[outByteOffset++] = static_cast<char>(inBuffer[inByteOffset++] + 128);
		sampleCount--;
	}
}

void TConversionTool::swapOrder16(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount)
{
	while (sampleCount > 0)
	{
		outBuffer[outByteOffset++] = inBuffer[inByteOffset + 1];
		outBuffer[outByteOffset++] = inBuffer[inByteOffset++];
		inByteOffset++;
		sampleCount--;
	}
}

void TConversionTool::swapOrder24(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount)
{
	while (sampleCount > 0)
	{
		outBuffer[outByteOffset++] = inBuffer[inByteOffset + 2];
		outByteOffset++;
		outBuffer[outByteOffset++] = inBuffer[inByteOffset++];
		inByteOffset++;
		inByteOffset++;
		sampleCount--;
	}
}

void TConversionTool::swapOrder32(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount)
{
	while (sampleCount > 0)
	{
		outBuffer[outByteOffset++] = inBuffer[inByteOffset + 3];
		outBuffer[outByteOffset++] = inBuffer[inByteOffset + 2];
		outBuffer[outByteOffset++] = inBuffer[inByteOffset + 1];
		outBuffer[outByteOffset++] = inBuffer[inByteOffset++];
		inByteOffset++;
		inByteOffset++;
		inByteOffset++;
		sampleCount--;
	}
}

void TConversionTool::shortToBytes16(short sample, std::vector<char> &buffer, int byteOffset, bool bigEndian)
{
	intToBytes16(sample, buffer, byteOffset, bigEndian);
}

void TConversionTool::intToBytes16(int sample, std::vector<char> &buffer, int byteOffset, bool bigEndian)
{
	if (bigEndian)
	{
		buffer[byteOffset++] = static_cast<char>(sample >> 8);
		buffer[byteOffset] = static_cast<char>(sample & 0xFF);
	}
	else
	{
		buffer[byteOffset++] = static_cast<char>(sample & 0xFF);
		buffer[byteOffset] = static_cast<char>(sample >> 8);
	}
}

void TConversionTool::intToBytes24(int sample, std::vector<char> &buffer, int byteOffset, bool bigEndian)
{
	if (bigEndian)
	{
		buffer[byteOffset++] = static_cast<char>(sample >> 16);
		buffer[byteOffset++] = static_cast<char>((static_cast<int>(static_cast<unsigned int>(sample) >> 8)) & 0xFF);
		buffer[byteOffset] = static_cast<char>(sample & 0xFF);
	}
	else
	{
		buffer[byteOffset++] = static_cast<char>(sample & 0xFF);
		buffer[byteOffset++] = static_cast<char>((static_cast<int>(static_cast<unsigned int>(sample) >> 8)) & 0xFF);
		buffer[byteOffset] = static_cast<char>(sample >> 16);
	}
}

void TConversionTool::intToBytes32(int sample, std::vector<char> &buffer, int byteOffset, bool bigEndian)
{
	if (bigEndian)
	{
		buffer[byteOffset++] = static_cast<char>(sample >> 24);
		buffer[byteOffset++] = static_cast<char>((static_cast<int>(static_cast<unsigned int>(sample) >> 16)) & 0xFF);
		buffer[byteOffset++] = static_cast<char>((static_cast<int>(static_cast<unsigned int>(sample) >> 8)) & 0xFF);
		buffer[byteOffset] = static_cast<char>(sample & 0xFF);
	}
	else
	{
		buffer[byteOffset++] = static_cast<char>(sample & 0xFF);
		buffer[byteOffset++] = static_cast<char>((static_cast<int>(static_cast<unsigned int>(sample) >> 8)) & 0xFF);
		buffer[byteOffset++] = static_cast<char>((static_cast<int>(static_cast<unsigned int>(sample) >> 16)) & 0xFF);
		buffer[byteOffset] = static_cast<char>(sample >> 24);
	}
}

char TConversionTool::linear2ulaw(int sample)
{
	int sign, exponent, mantissa, ulawbyte;

	if (sample > 32767)
	{
		sample = 32767;
	}
else if (sample < -32768)
{
	sample = -32768;
}
	/* Get the sample into sign-magnitude. */
	sign = (sample >> 8) & 0x80; // set aside the sign
	if (sign != 0)
	{
		sample = -sample; // get magnitude
	}
	if (sample > CLIP)
	{
		sample = CLIP; // clip the magnitude
	}

	/* Convert from 16 bit linear to ulaw. */
	sample = sample + BIAS;
	exponent = exp_lut1_tconv[(sample >> 7) & 0xFF];
	mantissa = (sample >> (exponent + 3)) & 0x0F;
	ulawbyte = ~(sign | (exponent << 4) | mantissa);
	if (ZEROTRAP)
	{
		if (ulawbyte == 0)
		{
			ulawbyte = 0x02; // optional CCITT trap
		}
	}
	return (static_cast<char>(ulawbyte));
}

std::vector<short> TConversionTool::u2l = {-32124, -31100, -30076, -29052, -28028, -27004, -25980, -24956, -23932, -22908, -21884, -20860, -19836, -18812, -17788, -16764, -15996, -15484, -14972, -14460, -13948, -13436, -12924, -12412, -11900, -11388, -10876, -10364, -9852, -9340, -8828, -8316, -7932, -7676, -7420, -7164, -6908, -6652, -6396, -6140, -5884, -5628, -5372, -5116, -4860, -4604, -4348, -4092, -3900, -3772, -3644, -3516, -3388, -3260, -3132, -3004, -2876, -2748, -2620, -2492, -2364, -2236, -2108, -1980, -1884, -1820, -1756, -1692, -1628, -1564, -1500, -1436, -1372, -1308, -1244, -1180, -1116, -1052, -988, -924, -876, -844, -812, -780, -748, -716, -684, -652, -620, -588, -556, -524, -492, -460, -428, -396, -372, -356, -340, -324, -308, -292, -276, -260, -244, -228, -212, -196, -180, -164, -148, -132, -120, -112, -104, -96, -88, -80, -72, -64, -56, -48, -40, -32, -24, -16, -8, 0, 32124, 31100, 30076, 29052, 28028, 27004, 25980, 24956, 23932, 22908, 21884, 20860, 19836, 18812, 17788, 16764, 15996, 15484, 14972, 14460, 13948, 13436, 12924, 12412, 11900, 11388, 10876, 10364, 9852, 9340, 8828, 8316, 7932, 7676, 7420, 7164, 6908, 6652, 6396, 6140, 5884, 5628, 5372, 5116, 4860, 4604, 4348, 4092, 3900, 3772, 3644, 3516, 3388, 3260, 3132, 3004, 2876, 2748, 2620, 2492, 2364, 2236, 2108, 1980, 1884, 1820, 1756, 1692, 1628, 1564, 1500, 1436, 1372, 1308, 1244, 1180, 1116, 1052, 988, 924, 876, 844, 812, 780, 748, 716, 684, 652, 620, 588, 556, 524, 492, 460, 428, 396, 372, 356, 340, 324, 308, 292, 276, 260, 244, 228, 212, 196, 180, 164, 148, 132, 120, 112, 104, 96, 88, 80, 72, 64, 56, 48, 40, 32, 24, 16, 8, 0};

short TConversionTool::ulaw2linear(char ulawbyte)
{
	return u2l[ulawbyte & 0xFF];
}

void TConversionTool::pcm162ulaw(std::vector<char> &buffer, int byteOffset, int sampleCount, bool bigEndian)
{
	int shortIndex = byteOffset;
	int ulawIndex = shortIndex;
	if (bigEndian)
	{
		while (sampleCount > 0)
		{
			buffer[ulawIndex++] = linear2ulaw(bytesToInt16(buffer[shortIndex], buffer[shortIndex + 1]));
			shortIndex++;
			shortIndex++;
			sampleCount--;
		}
	}
	else
	{
		while (sampleCount > 0)
		{
			buffer[ulawIndex++] = linear2ulaw(bytesToInt16(buffer[shortIndex + 1], buffer[shortIndex]));
			shortIndex++;
			shortIndex++;
			sampleCount--;
		}
	}
}

void TConversionTool::pcm162ulaw(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount, bool bigEndian)
{
	int shortIndex = inByteOffset;
	int ulawIndex = outByteOffset;
	if (bigEndian)
	{
		while (sampleCount > 0)
		{
			outBuffer[ulawIndex++] = linear2ulaw(bytesToInt16(inBuffer[shortIndex], inBuffer[shortIndex + 1]));
			shortIndex++;
			shortIndex++;
			sampleCount--;
		}
	}
	else
	{
		while (sampleCount > 0)
		{
			outBuffer[ulawIndex++] = linear2ulaw(bytesToInt16(inBuffer[shortIndex + 1], inBuffer[shortIndex]));
			shortIndex++;
			shortIndex++;
			sampleCount--;
		}
	}
}

void TConversionTool::pcm82ulaw(std::vector<char> &buffer, int byteOffset, int sampleCount, bool signed_Renamed)
{
	sampleCount += byteOffset;
	if (signed_Renamed)
	{
		for (int i = byteOffset; i < sampleCount; i++)
		{
			buffer[i] = linear2ulaw(buffer[i] << 8);
		}
	}
	else
	{
		for (int i = byteOffset; i < sampleCount; i++)
		{
			buffer[i] = linear2ulaw((static_cast<char>(buffer[i] + 128)) << 8);
		}
	}
}

void TConversionTool::pcm82ulaw(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount, bool signed_Renamed)
{
	int ulawIndex = outByteOffset;
	int pcmIndex = inByteOffset;
	if (signed_Renamed)
	{
		while (sampleCount > 0)
		{
			outBuffer[ulawIndex++] = linear2ulaw(inBuffer[pcmIndex++] << 8);
			sampleCount--;
		}
	}
	else
	{
		while (sampleCount > 0)
		{
			outBuffer[ulawIndex++] = linear2ulaw((static_cast<char>(inBuffer[pcmIndex++] + 128)) << 8);
			sampleCount--;
		}
	}
}

void TConversionTool::ulaw2pcm16(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount, bool bigEndian)
{
	int shortIndex = outByteOffset;
	int ulawIndex = inByteOffset;
	while (sampleCount > 0)
	{
		intToBytes16(u2l[inBuffer[ulawIndex++] & 0xFF], outBuffer, shortIndex++, bigEndian);
		shortIndex++;
		sampleCount--;
	}
}

void TConversionTool::ulaw2pcm8(std::vector<char> &buffer, int byteOffset, int sampleCount, bool signed_Renamed)
{
	sampleCount += byteOffset;
	if (signed_Renamed)
	{
		for (int i = byteOffset; i < sampleCount; i++)
		{
			buffer[i] = static_cast<char>((u2l[buffer[i] & 0xFF] >> 8) & 0xFF);
		}
	}
	else
	{
		for (int i = byteOffset; i < sampleCount; i++)
		{
			buffer[i] = static_cast<char>((u2l[buffer[i] & 0xFF] >> 8) + 128);
		}
	}
}

void TConversionTool::ulaw2pcm8(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount, bool signed_Renamed)
{
	int ulawIndex = inByteOffset;
	int pcmIndex = outByteOffset;
	if (signed_Renamed)
	{
		while (sampleCount > 0)
		{
			outBuffer[pcmIndex++] = static_cast<char>((u2l[inBuffer[ulawIndex++] & 0xFF] >> 8) & 0xFF);
			sampleCount--;
		}
	}
	else
	{
		while (sampleCount > 0)
		{
			outBuffer[pcmIndex++] = static_cast<char>((u2l[inBuffer[ulawIndex++] & 0xFF] >> 8) + 128);
			sampleCount--;
		}
	}
}

char TConversionTool::linear2alaw(short pcm_val)
{
	char mask;
	char seg = 8;
	char aval;

	if (pcm_val >= 0)
	{
		mask = static_cast<char>(0xD5); // sign (7th) bit = 1
	}
	else
	{
		mask = 0x55; // sign bit = 0
		pcm_val = static_cast<short>(-pcm_val - 8);
	}

	/* Convert the scaled magnitude to segment number. */
	for (int i = 0; i < 8; i++)
	{
		if (pcm_val <= seg_end_tconv[i])
		{
			seg = static_cast<char>(i);
			break;
		}
	}

	/* Combine the sign, segment, and quantization bits. */
	if (seg >= 8) // out of range, return maximum value.
	{
		return static_cast<char>((0x7F ^ mask) & 0xFF);
	}
	else
	{
		aval = static_cast<char>(seg << SEG_SHIFT);
		if (seg < 2)
		{
			aval |= (pcm_val >> 4) & QUANT_MASK;
		}
		else
		{
			aval |= (pcm_val >> (seg + 3)) & QUANT_MASK;
		}
		return static_cast<char>((aval ^ mask) & 0xFF);
	}
}

std::vector<short> TConversionTool::a2l = {-5504, -5248, -6016, -5760, -4480, -4224, -4992, -4736, -7552, -7296, -8064, -7808, -6528, -6272, -7040, -6784, -2752, -2624, -3008, -2880, -2240, -2112, -2496, -2368, -3776, -3648, -4032, -3904, -3264, -3136, -3520, -3392, -22016, -20992, -24064, -23040, -17920, -16896, -19968, -18944, -30208, -29184, -32256, -31232, -26112, -25088, -28160, -27136, -11008, -10496, -12032, -11520, -8960, -8448, -9984, -9472, -15104, -14592, -16128, -15616, -13056, -12544, -14080, -13568, -344, -328, -376, -360, -280, -264, -312, -296, -472, -456, -504, -488, -408, -392, -440, -424, -88, -72, -120, -104, -24, -8, -56, -40, -216, -200, -248, -232, -152, -136, -184, -168, -1376, -1312, -1504, -1440, -1120, -1056, -1248, -1184, -1888, -1824, -2016, -1952, -1632, -1568, -1760, -1696, -688, -656, -752, -720, -560, -528, -624, -592, -944, -912, -1008, -976, -816, -784, -880, -848, 5504, 5248, 6016, 5760, 4480, 4224, 4992, 4736, 7552, 7296, 8064, 7808, 6528, 6272, 7040, 6784, 2752, 2624, 3008, 2880, 2240, 2112, 2496, 2368, 3776, 3648, 4032, 3904, 3264, 3136, 3520, 3392, 22016, 20992, 24064, 23040, 17920, 16896, 19968, 18944, 30208, 29184, 32256, 31232, 26112, 25088, 28160, 27136, 11008, 10496, 12032, 11520, 8960, 8448, 9984, 9472, 15104, 14592, 16128, 15616, 13056, 12544, 14080, 13568, 344, 328, 376, 360, 280, 264, 312, 296, 472, 456, 504, 488, 408, 392, 440, 424, 88, 72, 120, 104, 24, 8, 56, 40, 216, 200, 248, 232, 152, 136, 184, 168, 1376, 1312, 1504, 1440, 1120, 1056, 1248, 1184, 1888, 1824, 2016, 1952, 1632, 1568, 1760, 1696, 688, 656, 752, 720, 560, 528, 624, 592, 944, 912, 1008, 976, 816, 784, 880, 848};

short TConversionTool::alaw2linear(char ulawbyte)
{
	return a2l[ulawbyte & 0xFF];
}

void TConversionTool::pcm162alaw(std::vector<char> &buffer, int byteOffset, int sampleCount, bool bigEndian)
{
	int shortIndex = byteOffset;
	int alawIndex = shortIndex;
	if (bigEndian)
	{
		while (sampleCount > 0)
		{
			buffer[alawIndex++] = linear2alaw(bytesToShort16(buffer[shortIndex], buffer[shortIndex + 1]));
			shortIndex++;
			shortIndex++;
			sampleCount--;
		}
	}
	else
	{
		while (sampleCount > 0)
		{
			buffer[alawIndex++] = linear2alaw(bytesToShort16(buffer[shortIndex + 1], buffer[shortIndex]));
			shortIndex++;
			shortIndex++;
			sampleCount--;
		}
	}
}

void TConversionTool::pcm162alaw(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount, bool bigEndian)
{
	int shortIndex = inByteOffset;
	int alawIndex = outByteOffset;
	if (bigEndian)
	{
		while (sampleCount > 0)
		{
			outBuffer[alawIndex++] = linear2alaw(bytesToShort16(inBuffer[shortIndex], inBuffer[shortIndex + 1]));
			shortIndex++;
			shortIndex++;
			sampleCount--;
		}
	}
	else
	{
		while (sampleCount > 0)
		{
			outBuffer[alawIndex++] = linear2alaw(bytesToShort16(inBuffer[shortIndex + 1], inBuffer[shortIndex]));
			shortIndex++;
			shortIndex++;
			sampleCount--;
		}
	}
}

void TConversionTool::pcm82alaw(std::vector<char> &buffer, int byteOffset, int sampleCount, bool signed_Renamed)
{
	sampleCount += byteOffset;
	if (signed_Renamed)
	{
		for (int i = byteOffset; i < sampleCount; i++)
		{
			buffer[i] = linear2alaw(static_cast<short>(buffer[i] << 8));
		}
	}
	else
	{
		for (int i = byteOffset; i < sampleCount; i++)
		{
			buffer[i] = linear2alaw(static_cast<short>((static_cast<char>(buffer[i] + 128)) << 8));
		}
	}
}

void TConversionTool::pcm82alaw(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount, bool signed_Renamed)
{
	int alawIndex = outByteOffset;
	int pcmIndex = inByteOffset;
	if (signed_Renamed)
	{
		while (sampleCount > 0)
		{
			outBuffer[alawIndex++] = linear2alaw(static_cast<short>(inBuffer[pcmIndex++] << 8));
			sampleCount--;
		}
	}
	else
	{
		while (sampleCount > 0)
		{
			outBuffer[alawIndex++] = linear2alaw(static_cast<short>((static_cast<char>(inBuffer[pcmIndex++] + 128)) << 8));
			sampleCount--;
		}
	}
}

void TConversionTool::alaw2pcm8(std::vector<char> &buffer, int byteOffset, int sampleCount, bool signed_Renamed)
{
	sampleCount += byteOffset;
	if (signed_Renamed)
	{
		for (int i = byteOffset; i < sampleCount; i++)
		{
			buffer[i] = static_cast<char>((a2l[buffer[i] & 0xFF] >> 8) & 0xFF);
		}
	}
	else
	{
		for (int i = byteOffset; i < sampleCount; i++)
		{
			buffer[i] = static_cast<char>((a2l[buffer[i] & 0xFF] >> 8) + 128);
		}
	}
}

void TConversionTool::alaw2pcm8(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount, bool signed_Renamed)
{
	int alawIndex = inByteOffset;
	int pcmIndex = outByteOffset;
	if (signed_Renamed)
	{
		while (sampleCount > 0)
		{
			outBuffer[pcmIndex++] = static_cast<char>((a2l[inBuffer[alawIndex++] & 0xFF] >> 8) & 0xFF);
			sampleCount--;
		}
	}
	else
	{
		while (sampleCount > 0)
		{
			outBuffer[pcmIndex++] = static_cast<char>((a2l[inBuffer[alawIndex++] & 0xFF] >> 8) + 128);
			sampleCount--;
		}
	}
}

void TConversionTool::alaw2pcm16(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount, bool bigEndian)
{
	int shortIndex = outByteOffset;
	int alawIndex = inByteOffset;
	while (sampleCount > 0)
	{
		intToBytes16(a2l[inBuffer[alawIndex++] & 0xFF], outBuffer, shortIndex++, bigEndian);
		shortIndex++;
		sampleCount--;
	}
}

std::vector<char> TConversionTool::u2a = {-86, -85, -88, -87, -82, -81, -84, -83, -94, -93, -96, -95, -90, -89, -92, -91, -70, -69, -72, -71, -66, -65, -68, -67, -78, -77, -80, -79, -74, -73, -76, -75, -118, -117, -120, -119, -114, -113, -116, -115, -126, -125, -128, -127, -122, -121, -124, -123, -101, -104, -103, -98, -97, -100, -99, -110, -109, -112, -111, -106, -105, -108, -107, -22, -24, -23, -18, -17, -20, -19, -30, -29, -32, -31, -26, -25, -28, -27, -6, -8, -2, -1, -4, -3, -14, -13, -16, -15, -10, -9, -12, -11, -53, -55, -49, -51, -62, -61, -64, -63, -58, -57, -60, -59, -38, -37, -40, -39, -34, -33, -36, -35, -46, -46, -45, -45, -48, -48, -47, -47, -42, -42, -41, -41, -44, -44, -43, -43, 42, 43, 40, 41, 46, 47, 44, 45, 34, 35, 32, 33, 38, 39, 36, 37, 58, 59, 56, 57, 62, 63, 60, 61, 50, 51, 48, 49, 54, 55, 52, 53, 10, 11, 8, 9, 14, 15, 12, 13, 2, 3, 0, 1, 6, 7, 4, 5, 27, 24, 25, 30, 31, 28, 29, 18, 19, 16, 17, 22, 23, 20, 21, 106, 104, 105, 110, 111, 108, 109, 98, 99, 96, 97, 102, 103, 100, 101, 122, 120, 126, 127, 124, 125, 114, 115, 112, 113, 118, 119, 116, 117, 75, 73, 79, 77, 66, 67, 64, 65, 70, 71, 68, 69, 90, 91, 88, 89, 94, 95, 92, 93, 82, 82, 83, 83, 80, 80, 81, 81, 86, 86, 87, 87, 84, 84, 85, 85};

char TConversionTool::ulaw2alaw(char sample)
{
	return u2a[sample & 0xFF];
}

void TConversionTool::ulaw2alaw(std::vector<char> &buffer, int byteOffset, int sampleCount)
{
	sampleCount += byteOffset;
	for (int i = byteOffset; i < sampleCount; i++)
	{
		buffer[i] = u2a[buffer[i] & 0xFF];
	}
}

void TConversionTool::ulaw2alaw(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount)
{
	int ulawIndex = outByteOffset;
	int alawIndex = inByteOffset;
	while (sampleCount > 0)
	{
		outBuffer[alawIndex++] = u2a[inBuffer[ulawIndex++] & 0xFF];
		sampleCount--;
	}
}

std::vector<char> TConversionTool::a2u = {-86, -85, -88, -87, -82, -81, -84, -83, -94, -93, -96, -95, -90, -89, -92, -91, -71, -70, -73, -72, -67, -66, -69, -68, -79, -78, -80, -80, -75, -74, -77, -76, -118, -117, -120, -119, -114, -113, -116, -115, -126, -125, -128, -127, -122, -121, -124, -123, -102, -101, -104, -103, -98, -97, -100, -99, -110, -109, -112, -111, -106, -105, -108, -107, -30, -29, -32, -31, -26, -25, -28, -27, -35, -35, -36, -36, -33, -33, -34, -34, -12, -10, -16, -14, -4, -2, -8, -6, -22, -21, -24, -23, -18, -17, -20, -19, -56, -55, -58, -57, -52, -51, -54, -53, -64, -63, -65, -65, -60, -59, -62, -61, -42, -41, -44, -43, -38, -37, -40, -39, -49, -49, -50, -50, -46, -45, -48, -47, 42, 43, 40, 41, 46, 47, 44, 45, 34, 35, 32, 33, 38, 39, 36, 37, 57, 58, 55, 56, 61, 62, 59, 60, 49, 50, 48, 48, 53, 54, 51, 52, 10, 11, 8, 9, 14, 15, 12, 13, 2, 3, 0, 1, 6, 7, 4, 5, 26, 27, 24, 25, 30, 31, 28, 29, 18, 19, 16, 17, 22, 23, 20, 21, 98, 99, 96, 97, 102, 103, 100, 101, 93, 93, 92, 92, 95, 95, 94, 94, 116, 118, 112, 114, 124, 126, 120, 122, 106, 107, 104, 105, 110, 111, 108, 109, 72, 73, 70, 71, 76, 77, 74, 75, 64, 65, 63, 63, 68, 69, 66, 67, 86, 87, 84, 85, 90, 91, 88, 89, 79, 79, 78, 78, 82, 83, 80, 81};

char TConversionTool::alaw2ulaw(char sample)
{
	return a2u[sample & 0xFF];
}

void TConversionTool::alaw2ulaw(std::vector<char> &buffer, int byteOffset, int sampleCount)
{
	sampleCount += byteOffset;
	for (int i = byteOffset; i < sampleCount; i++)
	{
		buffer[i] = a2u[buffer[i] & 0xFF];
	}
}

void TConversionTool::alaw2ulaw(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount)
{
	int ulawIndex = outByteOffset;
	int alawIndex = inByteOffset;
	while (sampleCount > 0)
	{
		outBuffer[ulawIndex++] = a2u[inBuffer[alawIndex++] & 0xFF];
		sampleCount--;
	}
}

void TConversionTool::changeOrderOrSign(std::vector<char> &buffer, int nOffset, int nByteLength, int nBytesPerSample)
{
	switch (nBytesPerSample)
	{
	case 1:
		convertSign8(buffer, nOffset, nByteLength);
		break;

	case 2:
		swapOrder16(buffer, nOffset, nByteLength / 2);
		break;

	case 3:
		swapOrder24(buffer, nOffset, nByteLength / 3);
		break;

	case 4:
		swapOrder32(buffer, nOffset, nByteLength / 4);
		break;
	}
}

void TConversionTool::changeOrderOrSign(std::vector<char> &inBuffer, int nInOffset, std::vector<char> &outBuffer, int nOutOffset, int nByteLength, int nBytesPerSample)
{
	switch (nBytesPerSample)
	{
	case 1:
		convertSign8(inBuffer, nInOffset, outBuffer, nOutOffset, nByteLength);
		break;

	case 2:
		swapOrder16(inBuffer, nInOffset, outBuffer, nOutOffset, nByteLength / 2);
		break;

	case 3:
		swapOrder24(inBuffer, nInOffset, outBuffer, nOutOffset, nByteLength / 3);
		break;

	case 4:
		swapOrder32(inBuffer, nInOffset, outBuffer, nOutOffset, nByteLength / 4);
		break;
	}
}
