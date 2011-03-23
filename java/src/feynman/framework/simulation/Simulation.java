/*
 * $Header: /cvsroot/feynman/src/feynman/framework/simulation/Simulation.java,v 1.1.1.1 2002/11/12 02:25:42 wesley_bailey Exp $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/11/12 02:25:42 $
 * $Copyright: Copyright (C) 2002 Path Integral Software $
 */
package feynman.framework.simulation;

import java.io.Serializable;

/**
 * Bean that represents a simulation in the framework.  Many of the attributes of
 * the simulation bean are defined in the <em>Simulation.properties</em> file by 
 * the user of the framework.
 * <p/>
 * The <b>Controller</b> class uses the simulation bean to control the creation
 * of the correct classes for the simulation.
 *
 * @author Wes Bailey
 * @version $Revision: 1.1.1.1 $ $Date: 2002/11/12 02:25:42 $
 */
public class Simulation implements Serializable {
	
	// Construct a private instance of the class.
	private static final Simulation INSTANCE = new Simulation();
	
	// Define the instance variables.
	private String physicalSystemClass;
	private String physicalObjectClass;
	private String physicalObjectFactoryClass;
	private String physicalConfigurationClass;
	private String physicalAlgorithmClass;
	private String physicalMeasurementClass;
	private String finalReportClass;
	private boolean doFinalReport = false;
	private String dataStore;
	private String dataStoreFile;
	private boolean performMeasurement = true;
	private int numberMeasurements;
	private int numberPhysicalObjects;
	private int iterations;
	private double interval;
	private double startTime;
	private double time;
	private boolean running = true;
	
	private Simulation() {
		// singleton
	}
	
	/**
	 * Use this method to get an instance of the Simulation class.
	 */
	public static Simulation getInstance() {
		return INSTANCE;
	}
	
	/**
	 * Use this method to specify the PhysicalSystemClass.
	 *
	 * @param physicalSystemClass The name of the PhysicalSystem class
	 */
	public void setPhysicalSystemClass(String physicalSystemClass) {
		this.physicalSystemClass = physicalSystemClass;
	}
	
	/**
	 * Use this method to get the PhysicalSystemClass.
	 */
	public String getPhysicalSystemClass() {
		return physicalSystemClass;
	}
	
	/**
	 * Use this method to specify the PhysicalObjectClass.
	 *
	 * @param physicalSystemClass The name of the PhysicalObject class
	 */
	public void setPhysicalObjectClass(String physicalObjectClass) {
		this.physicalObjectClass = physicalObjectClass;
	}
	
	/**
	 * Use this method to get the PhysicalObjectClass.
	 */
	public String getPhysicalObjectClass() {
		return physicalObjectClass;
	}
	
	/**
	 * Use this method to specify the PhysicalObjectFactoryClass.
	 *
	 * @param physicalObjectFactoryClass The name of the PhysicalObjectFactory class
	 */
	public void setPhysicalObjectFactoryClass(String physicalObjectFactoryClass) {
		this.physicalObjectFactoryClass = physicalObjectFactoryClass;
	}
	
	/**
	 * Use this method to get the PhysicalObjectFactoryClass.
	 */
	public String getPhysicalObjectFactoryClass() {
		return physicalObjectFactoryClass;
	}
	
	/**
	 * Use this method to specify the PhysicalConfigurationClass.
	 *
	 * @param physicalConfigurationClass The name of the PhysicalConfiguration class
	 */
	public void setPhysicalConfigurationClass(String physicalConfigurationClass) {
		this.physicalConfigurationClass = physicalConfigurationClass;
	}
	
	/**
	 * Use this method to get the PhysicalConfigurationClass.
	 */
	public String getPhysicalConfigurationClass() {
		return physicalConfigurationClass;
	}
	
	/**
	 * Use this method to specify the PhysicalAlgorithmClass.
	 *
	 * @param physicalAlgorithmClass The name of the PhysicalAlgorithm class
	 */
	public void setPhysicalAlgorithmClass(String physicalAlgorithmClass) {
		this.physicalAlgorithmClass = physicalAlgorithmClass;
	}
	
	/**
	 * Use this method to get the PhysicalAlgorithmClass.
	 */
	public String getPhysicalAlgorithmClass() {
		return physicalAlgorithmClass;
	}
	
	/**
	 * Use this method to specify the PhysicalMeasurementClass.
	 *
	 * @param physicalMeasurementClass The name of the PhysicalMeasurement class
	 */
	public void setPhysicalMeasurementClass(String physicalMeasurementClass) {
		this.physicalMeasurementClass = physicalMeasurementClass;
	}
	
	/**
	 * Use this method to get the PhysicalMeasurementClass.
	 */
	public String getPhysicalMeasurementClass() {
		return physicalMeasurementClass;
	}
	
	/**
	 * Use this method to define a class that performs a summary report of the simulation.
	 *
	 * @param physicalSystemReportClass The class implementing <b>PhysicalSystemReport</b>.
	 */
	public void setFinalReportClass(String finalReportClass) {
		this.finalReportClass = finalReportClass;
	}
	
	/**
	 * Use this method to get the class for the final report.
	 */
	public String getFinalReportClass() {
		return finalReportClass;
	}
	
	/**
	 * Use this method to indicate a final report should be produced.
	 */
	public void setDoFinalReport(boolean doFinalReport) {
		this.doFinalReport = doFinalReport;
	}
	
	/**
	 * Use this method to query whether to produce a final report or not.
	 */
	public boolean getDoFinalReport() {
		return doFinalReport;
	}
	
	/** 
	 * Alternative query to produce a final report or not.
	 */
	public boolean doFinalReport() {
		return getDoFinalReport();
	}
	
	/**
	 * Use this method to specify the DataStore.
	 *
	 * @param dataStore The name of the DataStore type to use.
	 */
	public void setDataStore(String dataStore) {
		this.dataStore = dataStore;
	}
	
	/**
	 * Use this method to get the DateStore.
	 */
	public String getDataStore() {
		return dataStore;
	}
	
	/**
	 * Use this method to specify the DataStoreFile.
	 *
	 * @param dataStoreFile The name of the DataStore output file if the
	 * FileDataStore class is specified.
	 */
	public void setDataStoreFile(String dataStoreFile) {
		this.dataStoreFile = dataStoreFile;
	}
	
	/**
	 * Use this method to get the DateStoreFile.
	 */
	public String getDataStoreFile() {
		return dataStoreFile;
	}
	
	/**
	 * Use this method to specify to PerformMeasurement on/off.
	 *
	 * @param performMeasurement true or false boolean value for on/off.
	 */
	public void setPerformMeasurement(boolean performMeasurement) {
		this.performMeasurement = performMeasurement;
	}
	
	/**
	 * Use this method to get the PerformMeasurement value.
	 */
	public boolean getPerformMeasurement() {
		return performMeasurement;
	}
	
	/**
	 * Use this method to specify the number of Measurements to make if
	 * PerformMeasurement is set to true.
	 *
	 * @param numberMeasurements The number of measurements to take during the simulation.
	 */
	public void setNumberMeasurements(int numberMeasurements) {
		this.numberMeasurements = numberMeasurements;
	}
	
	/**
	 * Use this method to get the number of measurements the simulation is to perform.
	 */
	public int getNumberMeasurements() {
		return numberMeasurements;
	}
	
	/**
	 * Use this method to specify the number of physical objects to be created
	 * and used in the simulation.
	 *
	 * @param numberPhysicalObjects The number of physical objects to create.
	 */
	public void setNumberPhysicalObjects(int numberPhysicalObjects) {
		this.numberPhysicalObjects = numberPhysicalObjects;
	}
	
	/**
	 * Use this method to get the number of PhyscialObjects to create.
	 */
	public int getNumberPhysicalObjects() {
		return numberPhysicalObjects;
	}
	
	/**
	 * Use this method to specify the number of iterations to perform.
	 *
	 * @param iterations The number of iterations to perform.
	 */
	public void setIterations(int iterations) {
		this.iterations = iterations;
	}
	
	/**
	 * Use this method to get the iterations the simulation will perform.
	 */
	public int getIterations() {
		return iterations;
	}
	
	/**
	 * Use this method to specify the timestep interval to be used to calculate
	 * the running time.
	 *
	 * @param interval The interval to be used in the simulation.
	 */
	public void setInterval(double interval) {
		this.interval = interval;
	}
	
	/**
	 * Use this method to get the interval which is usually a timestep.
	 */
	public double getInterval() {
		return interval;
	}
	
	/**
	 * Use this method to specify the time at the start of the simulation.  This
	 * is a convenience method if a simulation has not been completed and a new
	 * one is being run as a continuation of the previous simulation.
	 *
	 * @param startTime The time at the start of the simulation.
	 */
	public void setStartTime(double startTime) {
		this.startTime = startTime;
	}
	
	/**
	 * Use this method to get the start time of the simulation.
	 */
	public double getStartTime() {
		return startTime;
	}
	
	/**
	 * Use this method to specify the time during any point during the simulation.
	 * It is usually updated during execution of the <em>calculate</em> of the 
	 * user defined implementation of the <b>PhysicalAlgorithm</b> class.
	 *
	 * @param time The current time in the simulation.
	 */
	public void setTime(double time) {
		this.time = time;
	}
	
	/**
	 * Use this method to get the current value of the time in the simulation.
	 */
	public double getTime() {
		return time;
	}
	
	/**
	 * Use this method to update the time during any point during the simulation.
	 * It is usually updated during execution of the <em>calculate</em> of the 
	 * user defined implementation of the <b>PhysicalAlgorithm</b> class.  In this
	 * method the time is incremented by the interval.  Use this method if you
	 * want the simulation to update itself.  Use setTime(time) method if you want
	 * to do it manually or have any special logic for updating the time in your
	 * implementation.
	 */
	public void updateTime() {
		time += interval;
	}
	
	/**
	 * Use this method to specify that the simulation is running and should continue
	 * to run.  If you have a physical condition that when met should stop the execution
	 * of the simulation even if the current number of iterations has not met the defined
	 * in the properties file, then use this method and the <b>Controller</b> class
	 * will halt the execution and write any file data to the <b>DataStore</b>
	 * <p>
	 * This method is typically updated in the <em>calculate</em> method implementation
	 * of the <b>PhysicalAlgorithm</b> class.
	 *
	 * @param running Boolean that indicates the simulation is running and should
	 * continue to run.  Set to true or false to indicate on or off.
	 */
	public void setRunning(boolean running) {
		this.running = running;
	}
	
	/**
	 * Use this method to get the boolean value for if the simulation is running.
	 */
	public boolean getRunning() {
		return running;
	}
	
	/**
	 * Method to test whether the simulation should still be running or not.  The
	 * <b>Controller</b> class uses this method so you should not have to in your
	 * implementation of a simulation.
	 */
	public boolean isRunning() {
		return getRunning();
	}
	
	/**
	 * Get a string representation of the object.
	 */
	public String toString() {
		StringBuffer sb = new StringBuffer();
		
		sb.append("simulation[");
		sb.append("physicalSystemClass=" + physicalSystemClass + ",");
		sb.append("physicalObjectClass=" + physicalObjectClass + ",");
		sb.append("physicalObjectFactoryClass=" + physicalObjectFactoryClass + ",");
		sb.append("physicalConfigurationClass=" + physicalConfigurationClass + ",");
		sb.append("physicalAlgorithmClass=" + physicalAlgorithmClass + ",");
		sb.append("physicalMeasurementClass=" + physicalMeasurementClass + ",");
		sb.append("finalReportClass=" + finalReportClass + ",");
		sb.append("doFinalReport=" + doFinalReport + ",");
		sb.append("DataStore=" + dataStore + ",");
		sb.append("DataStoreFile=" + dataStoreFile + ",");
		sb.append("PerformMeasurement=" + performMeasurement + ",");
		sb.append("numberMeasurements=" + numberMeasurements + ",");
		sb.append("numberPhysicalObject=" + numberPhysicalObjects + ",");
		sb.append("iterations=" + iterations + ",");
		sb.append("interval=" + interval + ",");
		sb.append("startTime=" + startTime + ",");
		sb.append("time=" + time);
		sb.append("]");
		
		return sb.toString();
	}
	
}
