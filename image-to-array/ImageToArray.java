import java.util.*;
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;

class ImageToArray {

  private String output;
  private BufferedImage image;
  private int width, height;
  private int[][] finalArray;

  public ImageToArray(String input, String output) {
      try {
        this.image = ImageIO.read(new File(input));
      } catch (IOException e) {
        //e.printStackTrace();
      }
      this.width = this.image.getWidth();
      this.height = this.image.getHeight();
      this.finalArray = new int[this.width][this.height];
      this.output = output;

      //Black: -16777216
      //White: -1
      //Invicible: 0
      process();
      try {
        writeArrays();
      } catch (IOException e) {

      }
      //Outputs black as 0 and white and alpha as 1
  }

  public static void main(String[] args) {
    ImageToArray ita = new ImageToArray(args[0], args[1]);
  }

  public void process() {
    for (int x = 0; x < this.width; x++) {
      for (int y = 0; y < this.height; y++) {
        int pixel = this.image.getRGB(x, y);
        if (pixel == -16777216) { //Black
          pixel = 1;
        } else if (pixel == 0) { //Alpha = 0
          pixel = 0;
        } else {
          pixel = 0;
        }
        this.finalArray[x][y] = pixel;
      }
    }
    System.out.println("Image converted.");
  }

  public void writeNotArrays() throws IOException {
      BufferedWriter writer = new BufferedWriter(new FileWriter(this.output));
      writer.write("{");
      for (int y = 0; y < this.height; y++) {
        for (int x = 0; x < this.width; x++) {
          writer.write(this.finalArray[x][y] + ", ");
        }
      }
    writer.write("}");
    writer.close();
    System.out.println("Image written.");
  }

  public void writeArrays() throws IOException {
      BufferedWriter writer = new BufferedWriter(new FileWriter(this.output));
      writer.write("{");
      writer.newLine();
      for (int x = 0; x < this.width; x++) {
        writer.write("{");
        for (int y = 0; y < this.height; y++) {
          if (y == this.height - 1) {
            writer.write(this.finalArray[x][y] + "");
          } else {
            writer.write(this.finalArray[x][y] + ", ");
          }
        }

        if (x == this.width - 1) {
          writer.write("}");
          writer.newLine();
        } else {
          writer.write("}, ");
          writer.newLine();
        }
      }
    writer.write("}");
    writer.close();
    System.out.println("Image written to " + this.output);
  }
}
