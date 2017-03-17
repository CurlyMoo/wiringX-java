package eu.jm0.wiringX;

import java.lang.IllegalArgumentException;

public class UByteArray {
	private byte[] b;
	
	public UByteArray(int size) {
		b = new byte[size];
	}

	public void Set(int index, short value) {
		if(value < 0 || value > Byte.MAX_VALUE - Byte.MIN_VALUE) {
			throw new IllegalArgumentException("Value out of Range");
		}

		b[index] = (byte) (value + Byte.MIN_VALUE);
	}

	public short Get(int index) {
		short r = b[index];
		r -= Byte.MIN_VALUE;
		return r;
	}

	public byte[] raw() {
		return b;
	}
}
