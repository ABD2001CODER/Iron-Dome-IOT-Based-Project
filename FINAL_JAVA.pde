// Processing Sketch: Dual Sensor Radar with Enhanced Label Clarity

import processing.serial.*;

Serial myPort;

String data = "";
int iAngle1 = 90, iDistance1 = 0;
int iAngle2 = 90, iDistance2 = 0;

void setup() {
  size(1600, 800); // Window size
  myPort = new Serial(this, "COM11", 9600);
  myPort.bufferUntil('.');
  smooth();
}

void draw() {
  fill(98, 245, 31);
  noStroke();
  fill(0, 6);
  rect(600, 400, width, height);

  drawRadar(350, 550, iAngle1, iDistance1, "Station 1");
  drawRadar(1000, 550, iAngle2, iDistance2, "Station 2");
  
  fill(0); // background text box (optional)
  rectMode(CENTER);
  rect(700, 50, 500, 60, 20); // black rounded box (optional)
  
  fill(0, 255, 0); // green radar text
  textAlign(CENTER, CENTER);
  textSize(46);
  text("RADAR VISUALIZATION", 700, 50); // centered top

}

void serialEvent(Serial p) {
  data = p.readStringUntil('.');
  data = trim(data);

  if (data != null && data.contains("S1:") && data.contains("S2:")) {
    try {
      int s1Start = data.indexOf("S1:") + 3;
      int s1End = data.indexOf("S2:") - 1;
      String s1Data = data.substring(s1Start, s1End).trim();
      String s2Data = data.substring(data.indexOf("S2:") + 3).trim();

      String[] s1Parts = s1Data.split(",");
      String[] s2Parts = s2Data.split(",");

      if (s1Parts.length == 2 && s2Parts.length == 2) {
        iAngle1 = int(s1Parts[0]);
        iDistance1 = int(s1Parts[1]);
        iAngle2 = int(s2Parts[0]);
        iDistance2 = int(s2Parts[1]);
      }
    } catch (Exception e) {
      println("Parsing error: " + e.getMessage());
    }
  }
}

void drawRadar(float cx, float cy, int angle, int distance, String label) {
  pushMatrix();
  translate(cx, cy);
  noFill();
  strokeWeight(2);
  stroke(98, 245, 31);

  // Draw concentric arcs and add distance labels
  for (int i = 1; i <= 10; i++) {
    float radius = width * (0.04 * i); // arc diameter
    arc(0, 0, radius, radius, PI, TWO_PI); // radar arc

    // Draw distance labels
    //fill(250, 90, 12);
    textAlign(CENTER, CENTER);
    textSize(12);
    float labelX = radius / 2 * cos(radians(180));  // Leftmost point on arc
    float labelY = radius / 2 * sin(radians(180));  // Bottom of arc
    text(i * 5 + "cm", labelX, labelY + 10);       // Offset text slightly downward
  }

  // Draw radial lines and angle labels (ordered from 0° to 180°)
for (int i = 0; i <= 180; i += 30) {
  float angleRad = radians(i);
  float lineLength = width * 0.210; // Adjust to match your arcs
  float labelRadius = lineLength +11; // Slightly outside the arc

  float x = lineLength * cos(angleRad);
  float y = -lineLength * sin(angleRad); // Negated Y for top-down screen

  // Draw the radial line
  line(0, 0, x, y);

  // Label position slightly outside
  float labelX = labelRadius * cos(angleRad);
  float labelY = -labelRadius * sin(angleRad);

  fill(98, 245, 31);
  textAlign(CENTER, CENTER);
  textSize(16);
  text(i + "°", labelX, labelY);
}



  // Draw rotating scanning line
  stroke(0, 255, 0);
  line(0, 0,
       (height - height * 0.12) * 0.5 * cos(radians(angle)),
       -(height - height * 0.12) * 0.5 * sin(radians(angle)));

  // Draw detected object point
  if (distance > 0 && distance <= 100) {
    float pixDist = distance * 6.5;
    if (distance <= 25) stroke(255, 0, 0);
    else if (distance <= 40) stroke(255, 255, 0);
    else stroke(0, 255, 0);
    strokeWeight(10);
    point(pixDist * cos(radians(angle)), -pixDist * sin(radians(angle)));
  }

  popMatrix();

  // Info box
  float labelX = (label.equals("Station 1")) ? 350 : 1000;
  float labelY = 620;

  fill(0, 180);
  noStroke();
  rectMode(CENTER);
  rect(labelX, labelY, 250, 90, 12);

  fill(0, 255, 0);
  textAlign(CENTER);
  textSize(22);
  text(label, labelX, labelY - 25);
  text("Angle: " + angle + "°", labelX, labelY);
  text("Distance: " + distance + " cm", labelX, labelY + 25);
}

 
