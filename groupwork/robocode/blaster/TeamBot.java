package blaster;

import robocode.*;

import java.awt.Color;
import java.util.*;
import robocode.util.*;
import robocode.control.*;

/**
 * blasters.TeamBot
 * 
 * Cody Christian - robot tracking
 * Jeff Rasmussen Bullet detection and evade, Ramming
 * Josh Braegger - Wall detection
 * 
 */

public class TeamBot extends AdvancedRobot  {
	
	//Config Variables
	private final int MAX_RETREAT_NUM = 2; //Number of shots taken before you retreat
	private final int MAX_RAM_COUNT = 10; //Number of times to ram
	private final int MIN_RAM_ENERGY = 30; //Min Energy for ram
	private final double LOCKON_VAL = 20; //if you do more damage then this I will get you
	private final int RETREAT_TURN_AMT = 180;
	private final int RETREAT_DISTANCE = 450;
	private final int MISS_MAX = 4;
	private final int WALL_MARGIN = 50;
	
	private String currentAction = "";
	private int ramCount = 0;
	private int retreatCount = 0;
	private boolean lockedOn = false;
	private boolean retreat = false;
	private String target = "";
	private HashMap damageHM = new HashMap();
	private String lastScannedName = "";
	private double lastScannedEnergy = 0;
	private boolean evadeRight = true;
	private double firePower = 0;
	private int missCount = 0;
	private double lastEnemyHeading;
	private int ramTryCount = 0;

	
	public void run() {
		setAdjustRadarForRobotTurn(true);
		setAdjustGunForRobotTurn(true);
		setAdjustRadarForGunTurn(true);
		
        addCustomEvent(new Condition("wallAvoidance") {
            public boolean test() {
                return (
                    // we're too close to the left wall
                    (getX() <= WALL_MARGIN ||
                     // or we're too close to the right wall
                     getX() >= getBattleFieldWidth() - WALL_MARGIN ||
                     // or we're too close to the bottom wall
                     getY() <= WALL_MARGIN ||
                     // or we're too close to the top wall
                     getY() >= getBattleFieldHeight() - WALL_MARGIN)
                );
            }
		});
		
		setColors(Color.black,Color.blue,Color.black);
		setScanColor(Color.red);
		
		setEventPriority("HitRobotEvent", 6);
		setEventPriority("HitWallEvent", 5);

		while(true) {
			//Radar movement
			turnRadarRightRadians(Double.POSITIVE_INFINITY);
			
        }
	}

	private boolean detectEnergyDrop(String botName, double botEnergy)
	{
		boolean retVal = false;
		if(lastScannedName.length() == 0)
		{
			lastScannedName = botName;
			lastScannedEnergy = botEnergy;
		}
		else
		{
			if(lastScannedName == botName)
			{
				double energyDiff = lastScannedEnergy - botEnergy;
				if(energyDiff <= 3 && energyDiff >= .1 )
				{
					out.println("Detected Energy Drop! Possible Shot incomming!");	
					retVal = true;
				}
			
			}
			lastScannedName = botName;
			lastScannedEnergy = botEnergy;
		}
		
		return retVal;
	}
	
	private double getFirePower(double distance)
	{
		double fp = 0;
		if (distance < 100 && getEnergy() > 20)
			fp = Rules.MAX_BULLET_POWER;
		else if (distance < 150)
			fp = (Rules.MAX_BULLET_POWER/1.5);
		else if (distance < 175)
			fp = (Rules.MAX_BULLET_POWER/2);
		else if (distance < 225)
			fp = (Rules.MAX_BULLET_POWER/3);
		else if (distance < 300)
			fp = (Rules.MAX_BULLET_POWER/9);
		
		return fp;
	}
	
	public void onScannedRobot(ScannedRobotEvent e) {
		//out.println(e.getVelocity());
		
		double absoluteBearing = getHeading() + e.getBearing();
		double bearingFromRadar = normalRelativeAngle(absoluteBearing - getRadarHeading());
		double bearingFromGun = normalRelativeAngle(absoluteBearing - getGunHeading());
		boolean evadeBullet = false;
		
		//detect energy drop
		evadeBullet = detectEnergyDrop(e.getName(), e.getEnergy());
		
		if(lockedOn)
		{
			if(e.getName() != target)
			{
				return;
			}
		}
		
		// lock the radar
		if(bearingFromRadar > 0)
			setTurnRadarRight(bearingFromRadar);
		else
			setTurnRadarLeft(-bearingFromRadar);
		
		// lock the gun
		if(bearingFromGun > 0)
			setTurnGunRight(bearingFromGun);
		else
			setTurnGunLeft(-bearingFromGun);
		
		if( (getTurnRemaining() == 0) && (currentAction.length() > 0) && (currentAction != "Ramming"))
		{
			//out.println("Current Action Reset");
			currentAction = "";
		}
		//else if(currentAction.length() > 0)
			//out.println(currentAction+ " turn remaining:"+getTurnRemaining());
		
		if(currentAction.length() == 0)
		{
			//disable evade
			//evadeBullet = false;
			if(evadeBullet)
			{
				currentAction = "Evade";
				//get out of the way
				evadeRight= !evadeRight;
				if(evadeRight)
				{
					if(getTurnRemaining() <= 0)
						setTurnRight(90);
				}
				else
				{	
					if(getTurnRemaining() <= 0)
						setTurnLeft(90);
				}
				setAhead(100);	
				execute();
			}
			else
			{
				//Turn towards the bot
				currentAction = "Turn Towards Bot";
				setTurnRight(e.getBearing());
			}
			
			if(e.getDistance() > 50 )
			{
				if (e.getDistance() < 150)
					setAhead(e.getDistance()/2);
				else if (e.getDistance() < 175)
					setAhead(e.getDistance()/2.2);
				else if (e.getDistance() < 225)
					setAhead(e.getDistance()/1.4);
				else if (e.getDistance() < 300)
					setAhead(e.getDistance()/1.3);
				else
					setAhead(e.getDistance()/1.2);
			}
			else
			{
				currentAction = "Ramming";
			}
			
			// if we retreat then we trump any other movements
			if(retreat)
			{
				currentAction = "RETREAT";
				if (e.getBearing() > 0)
				{
					setTurnRight(RETREAT_TURN_AMT);
					if (e.getBearing() > -90 && e.getBearing() <= 90)
						setBack(RETREAT_DISTANCE);
					else
						setAhead(RETREAT_DISTANCE);	
				}
				else
				{
					missCount = 0;
					setTurnLeft(RETREAT_TURN_AMT);
					if (e.getBearing() > -90 && e.getBearing() <= 90)
			           setBack(RETREAT_DISTANCE);
					else
			           setAhead(RETREAT_DISTANCE);
				}
				retreat=false;
			}
		}
		
		if(currentAction.equals("Ramming"))
		{
			ramTryCount++;
			if(ramTryCount > 30) //ramming is probbaly not working, we are probably just chasing him. Switch stratagy
			{
				currentAction="";
				
			}
			
			if (ramCount < MAX_RAM_COUNT && getEnergy() > MIN_RAM_ENERGY )
			{
				// ram and fire
				out.println("Ramming");
				while(getTurnRemaining() != 0)
				{
					execute();
				}
				
				setTurnRight(e.getBearing());
				
				if(e.getDistance() > 100)
					setAhead(100);
				else
				{
					setAhead(e.getDistance() + 5);
					ramCount++;
				}
			}
			else
			{
				currentAction = "";
				setTurnRight(90);
				setBack(300);
				ramCount=0;
				while(getTurnRemaining() != 0)
				{
					execute();
				}
			}
		}
		else
		{
			//disable fire
			//firePower = 0;
			//out.println("firepower = " + firePower);
			setFire(getFirePower(e.getDistance()));
		}
		
		
		
		execute();
	}

	public void onHitByBullet(HitByBulletEvent e) {
		// update the damage hashmap
		// use this for tracking the bot that is beating me up
		double damage = 4 * e.getPower();
		if(e.getPower() > 1)
			damage += 2 * (e.getPower()-1);
		
		if ( (damageHM.size() > 0) && (damageHM.containsKey(e.getName())) )
		{
			damageHM.put(e.getName(), (Double) damageHM.get(e.getName()) + damage );
		}
		else
		{
			damageHM.put(e.getName(), damage );
			damageHM = getSortedMap(damageHM);
		}
		
		//Should I go after anyone?
		if(damageHM.size() > 0)
		{
			String meanBot = (String) new ArrayList( damageHM.keySet() ).get(damageHM.size()-1);
			if( ((Double) damageHM.get( meanBot ) >= LOCKON_VAL) && (!lockedOn) )
			{
				out.println("DESTROY "+ meanBot);
				target = meanBot;
				lockedOn = true;
			}
		}
		
		//Retreat Code
		double absoluteBearing = getHeading() + e.getBearing();
		double bearingFromRadar = normalRelativeAngle(absoluteBearing - getRadarHeading());
		double bearingFromGun = normalRelativeAngle(absoluteBearing - getGunHeading());
		
		if(retreatCount != MAX_RETREAT_NUM)
		{
			retreatCount++;
			out.println("Hit #"+retreatCount);
			retreat = false;
			return;
		}
		
		retreat = true;
		retreatCount = 0;
	}
	
	public void onBulletHit(BulletHitEvent e) {
		//fire again
		setFire(Rules.MAX_BULLET_POWER/1.25);
		execute();
	}
	
	public void onHitRobot(HitRobotEvent e) {
		if(!e.isMyFault())
		{
			setTurnRight(90);
			if (e.getBearing() > -90 && e.getBearing() <= 90) {
	           setBack(800);
			} else {
	           setAhead(800);
			}
			execute();
		}
		else if(currentAction.equals("Ramming"))
		{
			setFire(Rules.MAX_BULLET_POWER);
			execute();
			ramCount++;
		}
   }

	public void onRobotDeath(RobotDeathEvent e)
	{
		//remove the robot from damageHM
		if(damageHM.containsKey(e.getName()))
		{
			damageHM.remove(e.getName());
			out.println("Removed "+e.getName()+" from damageHM");
		}
		
		//no longer tracking it
		if(e.getName() == target)
		{
			target = "";
			lockedOn = false;
		}
	}
	
	public void onBulletMissed(BulletMissedEvent event) {
		out.println("Missed target");
		
		if(missCount == MISS_MAX)
		{
			out.println("Missed too many times. Try Ramming");
			currentAction = "Ramming";
		}
		else
			missCount++;
			out.println("missCount = "+missCount);
		
		}
	
	//Helpers
	private double normalRelativeAngle(double angle) {
		if (angle > -180 && angle <= 180) {
			return angle;
		}
		double fixedAngle = angle;

		while (fixedAngle <= -180) {
			fixedAngle += 360;
		}
		while (fixedAngle > 180) {
			fixedAngle -= 360;
		}
		return fixedAngle;
	}
	
	private HashMap getSortedMap(HashMap hmap)
	{
		HashMap map = new LinkedHashMap();
		List mapKeys = new ArrayList(hmap.keySet());
		List mapValues = new ArrayList(hmap.values());
		hmap.clear();
		TreeSet sortedSet = new TreeSet(mapValues);
		Object[] sortedArray = sortedSet.toArray();
		int size = sortedArray.length;
//			a) Ascending sort
		for (int i=0; i<size; i++)
		{
			map.put(mapKeys.get(mapValues.indexOf(sortedArray[i])), sortedArray[i]);
		}
		return map;
	}
	
	private int handlingWall = 0;
	
	public void onCustomEvent(CustomEvent e) {
	if (e.getCondition().getName().equals("wallAvoidance"))
	{
		if (handlingWall <= 0) {
            handlingWall = 1;
            setTurnRight(15);
            setAhead(10);
			handlingWall = 0;
		}
	}
}


}