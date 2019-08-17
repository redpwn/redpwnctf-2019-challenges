import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.File;

import javax.imageio.ImageIO;

public class MSB {
	public static void main(String args[]) throws Exception {
		BufferedImage img = ImageIO.read(new File("NIK_5652.JPG"));
		BufferedImage finImg = new BufferedImage(img.getWidth(), img.getHeight(), BufferedImage.TYPE_INT_ARGB);

		String encoded = "pizzas, pies, and pandas. flag{MSB_really_sucks}";
		byte[] bs = encoded.getBytes();
		String ret = "";
		for (byte b : bs) {
			String tmp = Integer.toBinaryString(b);
			while (tmp.length() < 8)
				tmp = "0" + tmp;

			ret += tmp;
		}

		System.out.println(ret);

		int index = 0;
		for (int i = 0; i < img.getWidth(); i++) {
			for (int z = 0; z < img.getHeight(); z++) {
				char curr = ret.charAt(index++);
				index %= ret.length();

				Color c = new Color(img.getRGB(i, z));
				int nextBlue = c.getBlue();
				if (curr == '0') {
					nextBlue &= ~(1 << 7);
				} else {
					nextBlue |= 1 << 7;
				}
				Color next = new Color(c.getRed(),
						Math.random() < 0.5 ? (c.getGreen() & ~(1 << 7)) : (c.getGreen() | (1 << 7)), nextBlue);
				finImg.setRGB(i, z, next.getRGB());
			}
		}

		ImageIO.write(finImg, "png", new File("lol.png"));
	}
}
