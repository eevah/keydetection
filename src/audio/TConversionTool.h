#pragma once

#include <vector>

/*
 *	TConversionTool.java
 *
 *	This file is part of Tritonus: http://www.tritonus.org/
 */

/*
 *  Copyright (c) 1999,2000 by Florian Bomers <http://www.bomers.de>
 *  Copyright (c) 2000 by Matthias Pfisterer
 *
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as published
 *   by the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Library General Public License for more details.
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

/*
|<---            this code is formatted to fit into 80 columns             --->|
*/

/// <summary>
/// Useful methods for converting audio data.
///
/// @author Florian Bomers
/// @author Matthias Pfisterer
/// </summary>

/*
For convenience, a list of available methods is maintained here.
Some hints:
- buffers: always byte arrays
- offsets: always in bytes
- sampleCount: number of SAMPLES to read/write, as opposed to FRAMES or BYTES!
- when in buffer and out buffer are given, the data is copied,
  otherwise it is replaced in the same buffer (buffer size is not checked!)
- a number (except "2") gives the number of bits in which format
  the samples have to be.
- >8 bits per sample is always treated signed.
- all functions are tried to be optimized - hints welcome !


** "high level" methods **
changeOrderOrSign(buffer, nOffset, nByteLength, nBytesPerSample)
changeOrderOrSign(inBuffer, nInOffset, outBuffer, nOutOffset, nByteLength, nBytesPerSample)


** PCM byte order and sign conversion **
void 	convertSign8(buffer, byteOffset, sampleCount)
void 	swapOrder16(buffer, byteOffset, sampleCount)
void 	swapOrder24(buffer, byteOffset, sampleCount)
void 	swapOrder32(buffer, byteOffset, sampleCount)
void 	convertSign8(inBuffer, inByteOffset, outBuffer, outByteOffset, sampleCount)
void 	swapOrder16(inBuffer, inByteOffset, outBuffer, outByteOffset, sampleCount)
void 	swapOrder24(inBuffer, inByteOffset, outBuffer, outByteOffset, sampleCount)
void 	swapOrder32(inBuffer, inByteOffset, outBuffer, outByteOffset, sampleCount)


** conversion functions for byte arrays **
** these are for reference to see how to implement these conversions **
short 	bytesToShort16(highByte, lowByte)
short 	bytesToShort16(buffer, byteOffset, bigEndian)
short 	bytesToInt16(highByte, lowByte)
short 	bytesToInt16(buffer, byteOffset, bigEndian)
short 	bytesToInt24(buffer, byteOffset, bigEndian)
short 	bytesToInt32(buffer, byteOffset, bigEndian)
void 	shortToBytes16(sample, buffer, byteOffset, bigEndian)
void 	intToBytes24(sample, buffer, byteOffset, bigEndian)
void 	intToBytes32(sample, buffer, byteOffset, bigEndian)


** ULAW <-> PCM **
byte 	linear2ulaw(int sample)
short 	ulaw2linear(int ulawbyte)
void 	pcm162ulaw(buffer, byteOffset, sampleCount, bigEndian)
void 	pcm162ulaw(inBuffer, inByteOffset, outBuffer, outByteOffset, sampleCount, bigEndian)
void 	pcm82ulaw(buffer, byteOffset, sampleCount, signed)
void 	pcm82ulaw(inBuffer, inByteOffset, outBuffer, outByteOffset, sampleCount, signed)
void 	ulaw2pcm16(inBuffer, inByteOffset, outBuffer, outByteOffset, sampleCount, bigEndian)
void 	ulaw2pcm8(buffer, byteOffset, sampleCount, signed)
void 	ulaw2pcm8(inBuffer, inByteOffset, outBuffer, outByteOffset, sampleCount, signed)


** ALAW <-> PCM **
byte linear2alaw(short pcm_val)
short alaw2linear(byte ulawbyte)
void pcm162alaw(inBuffer, inByteOffset, outBuffer, outByteOffset, sampleCount, bigEndian)
void pcm162alaw(buffer, byteOffset, sampleCount, bigEndian)
void pcm82alaw(buffer, byteOffset, sampleCount, signed)
void pcm82alaw(inBuffer, inByteOffset, outBuffer, outByteOffset, sampleCount, signed)
void alaw2pcm16(inBuffer, inByteOffset, outBuffer, outByteOffset, sampleCount, bigEndian)
void alaw2pcm8(buffer, byteOffset, sampleCount, signed)
void alaw2pcm8(inBuffer, inByteOffset, outBuffer, outByteOffset, sampleCount, signed)


** ULAW <-> ALAW **
byte 	ulaw2alaw(byte sample)
void 	ulaw2alaw(buffer, byteOffset, sampleCount)
void 	ulaw2alaw(inBuffer, inByteOffset, outBuffer, outByteOffset, sampleCount)
byte 	alaw2ulaw(byte sample)
void 	alaw2ulaw(buffer, byteOffset, sampleCount)
void 	alaw2ulaw(inBuffer, inByteOffset, outBuffer, outByteOffset, sampleCount)

*/

class TConversionTool
{

	///////////////// sign/byte-order conversion ///////////////////////////////////

public:
	static void convertSign8(std::vector<char> &buffer, int byteOffset, int sampleCount);

	static void swapOrder16(std::vector<char> &buffer, int byteOffset, int sampleCount);

	static void swapOrder24(std::vector<char> &buffer, int byteOffset, int sampleCount);

	static void swapOrder32(std::vector<char> &buffer, int byteOffset, int sampleCount);

	static void convertSign8(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount);

	static void swapOrder16(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount);

	static void swapOrder24(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount);

	static void swapOrder32(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount);



	/// <summary>
	/// Converts a sample of type <code>short</code> to 2 bytes in an array.
	/// <code>sample</code> is interpreted as signed (as Java does).
	/// <para>
	/// For little endian, buffer[byteOffset] is filled with low byte of sample,
	/// and buffer[byteOffset+1] is filled with high byte of sample.
	/// </para>
	/// <para> For big endian, this is reversed.
	/// </para>
	/// <para> This is a reference function.
	/// </para>
	/// </summary>
	static void shortToBytes16(short sample, std::vector<char> &buffer, int byteOffset, bool bigEndian);

	/// <summary>
	/// Converts a 16 bit sample of type <code>int</code> to 2 bytes in an array.
	/// <code>sample</code> is interpreted as signed (as Java does).
	/// <para>
	/// For little endian, buffer[byteOffset] is filled with low byte of sample,
	/// and buffer[byteOffset+1] is filled with high byte of sample + sign bit.
	/// </para>
	/// <para> For big endian, this is reversed.
	/// </para>
	/// <para> Before calling this function, it should be assured that <code>sample</code>
	/// is in the 16bit range - it will not be clipped.
	/// </para>
	/// <para> This is a reference function.
	/// </para>
	/// </summary>
	static void intToBytes16(int sample, std::vector<char> &buffer, int byteOffset, bool bigEndian);

	/// <summary>
	/// Converts a 24 bit sample of type <code>int</code> to 3 bytes in an array.
	/// <code>sample</code> is interpreted as signed (as Java does).
	/// <para>
	/// For little endian, buffer[byteOffset] is filled with low byte of sample,
	/// and buffer[byteOffset+2] is filled with the high byte of sample + sign bit.
	/// </para>
	/// <para> For big endian, this is reversed.
	/// </para>
	/// <para> Before calling this function, it should be assured that <code>sample</code>
	/// is in the 24bit range - it will not be clipped.
	/// </para>
	/// <para> This is a reference function.
	/// </para>
	/// </summary>
	static void intToBytes24(int sample, std::vector<char> &buffer, int byteOffset, bool bigEndian);


	/// <summary>
	/// Converts a 32 bit sample of type <code>int</code> to 4 bytes in an array.
	/// <code>sample</code> is interpreted as signed (as Java does).
	/// <para>
	/// For little endian, buffer[byteOffset] is filled with lowest byte of sample,
	/// and buffer[byteOffset+3] is filled with the high byte of sample + sign bit.
	/// </para>
	/// <para> For big endian, this is reversed.
	/// </para>
	/// <para> This is a reference function.
	/// </para>
	/// </summary>
	static void intToBytes32(int sample, std::vector<char> &buffer, int byteOffset, bool bigEndian);


	/////////////////////// ULAW ///////////////////////////////////////////

private:
	static const bool ZEROTRAP = true;
	static const short BIAS = 0x84;
	static const int CLIP = 32635;
	static std::vector<int> const exp_lut1_tconv;

	/// <summary>
	/// Converts a linear signed 16bit sample to a uLaw byte.
	/// Ported to Java by fb.
	/// <BR>Originally by:<BR>
	/// Craig Reese: IDA/Supercomputing Research Center <BR>
	/// Joe Campbell: Department of Defense <BR>
	/// 29 September 1989 <BR>
	/// </summary>
public:
	static char linear2ulaw(int sample);

	/* u-law to linear conversion table */
private:
	static std::vector<short> u2l;
public:
	static short ulaw2linear(char ulawbyte);



	/// <summary>
	/// Converts a buffer of signed 16bit big endian samples to uLaw.
	/// The uLaw bytes overwrite the original 16 bit values.
	/// The first byte-offset of the uLaw bytes is byteOffset.
	/// It will be written sampleCount/2 bytes.
	/// </summary>
	static void pcm162ulaw(std::vector<char> &buffer, int byteOffset, int sampleCount, bool bigEndian);

	/// <summary>
	/// Fills outBuffer with ulaw samples.
	/// reading starts from inBuffer[inByteOffset].
	/// writing starts at outBuffer[outByteOffset].
	/// There will be sampleCount*2 bytes read from inBuffer;
	/// There will be sampleCount <B>bytes</B> written to outBuffer.
	/// </summary>
	static void pcm162ulaw(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount, bool bigEndian);

	// TODO: either direct 8bit pcm to ulaw, or better conversion from 8bit to 16bit
	/// <summary>
	/// Converts a buffer of 8bit samples to uLaw.
	/// The uLaw bytes overwrite the original 8 bit values.
	/// The first byte-offset of the uLaw bytes is byteOffset.
	/// It will be written sampleCount bytes.
	/// </summary>
	static void pcm82ulaw(std::vector<char> &buffer, int byteOffset, int sampleCount, bool signed_Renamed);

	/// <summary>
	/// Fills outBuffer with ulaw samples.
	/// reading starts from inBuffer[inByteOffset].
	/// writing starts at outBuffer[outByteOffset].
	/// There will be sampleCount <B>bytes</B> written to outBuffer.
	/// </summary>
	static void pcm82ulaw(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount, bool signed_Renamed);

	/// <summary>
	/// Fills outBuffer with pcm signed 16 bit samples.
	/// reading starts from inBuffer[inByteOffset].
	/// writing starts at outBuffer[outByteOffset].
	/// There will be sampleCount bytes read from inBuffer;
	/// There will be sampleCount*2 bytes written to outBuffer.
	/// </summary>
	static void ulaw2pcm16(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount, bool bigEndian);


	// TODO: either direct 8bit pcm to ulaw, or better conversion from 8bit to 16bit
	/// <summary>
	/// Inplace-conversion of a ulaw buffer to 8bit samples.
	/// The 8bit bytes overwrite the original ulaw values.
	/// The first byte-offset of the uLaw bytes is byteOffset.
	/// It will be written sampleCount bytes.
	/// </summary>
	static void ulaw2pcm8(std::vector<char> &buffer, int byteOffset, int sampleCount, bool signed_Renamed);

	/// <summary>
	/// Fills outBuffer with ulaw samples.
	/// reading starts from inBuffer[inByteOffset].
	/// writing starts at outBuffer[outByteOffset].
	/// There will be sampleCount <B>bytes</B> written to outBuffer.
	/// </summary>
	static void ulaw2pcm8(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount, bool signed_Renamed);


	//////////////////// ALAW ////////////////////////////


	/*
	 * This source code is a product of Sun Microsystems, Inc. and is provided
	 * for unrestricted use.  Users may copy or modify this source code without
	 * charge.
	 *
	 * linear2alaw() - Convert a 16-bit linear PCM value to 8-bit A-law
	 *
	 * linear2alaw() accepts an 16-bit integer and encodes it as A-law data.
	 *
	 *		Linear Input Code	Compressed Code
	 *	------------------------	---------------
	 *	0000000wxyza			000wxyz
	 *	0000001wxyza			001wxyz
	 *	000001wxyzab			010wxyz
	 *	00001wxyzabc			011wxyz
	 *	0001wxyzabcd			100wxyz
	 *	001wxyzabcde			101wxyz
	 *	01wxyzabcdef			110wxyz
	 *	1wxyzabcdefg			111wxyz
	 *
	 * For further information see John C. Bellamy's Digital Telephony, 1982,
	 * John Wiley & Sons, pps 98-111 and 472-476.
	 */
private:
	static const char QUANT_MASK = 0xf; // Quantization field mask.
	static const char SEG_SHIFT = 4; // Left shift for segment number.
	static std::vector<short> const seg_end_tconv;

public:
	static char linear2alaw(short pcm_val); // 2's complement (16-bit range)

private:
	static std::vector<short> a2l;

public:
	static short alaw2linear(char ulawbyte);

	/// <summary>
	/// Converts a buffer of signed 16bit big endian samples to uLaw.
	/// The uLaw bytes overwrite the original 16 bit values.
	/// The first byte-offset of the uLaw bytes is byteOffset.
	/// It will be written sampleCount/2 bytes.
	/// </summary>
	static void pcm162alaw(std::vector<char> &buffer, int byteOffset, int sampleCount, bool bigEndian);

	/// <summary>
	/// Fills outBuffer with alaw samples.
	/// reading starts from inBuffer[inByteOffset].
	/// writing starts at outBuffer[outByteOffset].
	/// There will be sampleCount*2 bytes read from inBuffer;
	/// There will be sampleCount <B>bytes</B> written to outBuffer.
	/// </summary>
	static void pcm162alaw(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount, bool bigEndian);

	/// <summary>
	/// Converts a buffer of 8bit samples to alaw.
	/// The alaw bytes overwrite the original 8 bit values.
	/// The first byte-offset of the aLaw bytes is byteOffset.
	/// It will be written sampleCount bytes.
	/// </summary>
	static void pcm82alaw(std::vector<char> &buffer, int byteOffset, int sampleCount, bool signed_Renamed);

	/// <summary>
	/// Fills outBuffer with alaw samples.
	/// reading starts from inBuffer[inByteOffset].
	/// writing starts at outBuffer[outByteOffset].
	/// There will be sampleCount <B>bytes</B> written to outBuffer.
	/// </summary>
	static void pcm82alaw(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount, bool signed_Renamed);



	/// <summary>
	/// Converts an alaw buffer to 8bit pcm samples
	/// The 8bit bytes overwrite the original alaw values.
	/// The first byte-offset of the aLaw bytes is byteOffset.
	/// It will be written sampleCount bytes.
	/// </summary>
	static void alaw2pcm8(std::vector<char> &buffer, int byteOffset, int sampleCount, bool signed_Renamed);

	/// <summary>
	/// Fills outBuffer with alaw samples.
	/// reading starts from inBuffer[inByteOffset].
	/// writing starts at outBuffer[outByteOffset].
	/// There will be sampleCount <B>bytes</B> written to outBuffer.
	/// </summary>
	static void alaw2pcm8(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount, bool signed_Renamed);

	/// <summary>
	/// Fills outBuffer with pcm signed 16 bit samples.
	/// reading starts from inBuffer[inByteOffset].
	/// writing starts at outBuffer[outByteOffset].
	/// There will be sampleCount bytes read from inBuffer;
	/// There will be sampleCount*2 bytes written to outBuffer.
	/// </summary>
	static void alaw2pcm16(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount, bool bigEndian);

	//////////////////////// cross conversion alaw <-> ulaw ////////////////////////////////////////

private:
	static std::vector<char> u2a;

public:
	static char ulaw2alaw(char sample);

	/// <summary>
	/// Converts a buffer of uLaw samples to aLaw.
	/// </summary>
	static void ulaw2alaw(std::vector<char> &buffer, int byteOffset, int sampleCount);

	/// <summary>
	/// Fills outBuffer with alaw samples.
	/// </summary>
	static void ulaw2alaw(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount);

private:
	static std::vector<char> a2u;

public:
	static char alaw2ulaw(char sample);

	/// <summary>
	/// Converts a buffer of aLaw samples to uLaw.
	/// The uLaw bytes overwrite the original aLaw values.
	/// The first byte-offset of the uLaw bytes is byteOffset.
	/// It will be written sampleCount bytes.
	/// </summary>
	static void alaw2ulaw(std::vector<char> &buffer, int byteOffset, int sampleCount);

	/// <summary>
	/// Fills outBuffer with ulaw samples.
	/// reading starts from inBuffer[inByteOffset].
	/// writing starts at outBuffer[outByteOffset].
	/// There will be sampleCount <B>bytes</B> written to outBuffer.
	/// </summary>
	static void alaw2ulaw(std::vector<char> &inBuffer, int inByteOffset, std::vector<char> &outBuffer, int outByteOffset, int sampleCount);


	//////////////////////// high level methods /////////////////////////////////////////////////

	/*
	 *	!! Here, unlike other functions in this class, the length is
	 *	in bytes rather than samples !!
	 */
	static void changeOrderOrSign(std::vector<char> &buffer, int nOffset, int nByteLength, int nBytesPerSample);



	/*
	 *	!! Here, unlike other functions in this class, the length is
	 *	in bytes rather than samples !!
	 */
	static void changeOrderOrSign(std::vector<char> &inBuffer, int nInOffset, std::vector<char> &outBuffer, int nOutOffset, int nByteLength, int nBytesPerSample);
};

