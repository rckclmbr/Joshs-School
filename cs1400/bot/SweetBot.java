package jb;

import robocode.*;
import java.awt.Color;

/**
 * SweetBot - a robot by Josh Braegger
 */
public class SweetBot extends Robot
{
	/**
	 * run: SweetBot's default behavior
	 */
	public void run() {
		setColors(Color.black, Color.red, Color.red);
		while(true) {
			turnGunRight(30);
		}
	}

	/**
	 * onScannedRobot: What to do when you see another robot
	 */
	public void onScannedRobot(ScannedRobotEvent e) {
		double distance = e.getDistance();
		double force = 0;
		if (distance < 200) {
			force = 3;	
		}
		else {
			force = .5;	
		}
		fireBullet(force);
	}

	/**
	 * onHitByBullet: What to do when you're hit by a bullet
	 */
	public void onHitByBullet(HitByBulletEvent e) {
//		turnLeft(90 - e.getBearing());
		back(320);
		turnLeft(20);
		turnGunRight(200);
		
		int c = (int)(Math.random() * 10 % 3);
		switch (c) {
			case 0:
				turnGunRight(34);
				break;
			case 1:
				turnGunRight(30);
				ahead(20);
				break;
			case 2:
				turnLeft(30);
				turnGunRight(160);
				break;
			default:
				turnRight(120);	
		}
	}
	
}
