/*
 * $Header: /cvsroot/feynman/src/feynman/framework/controller/Controller.java,v 1.1.1.1 2002/11/12 02:25:41 wesley_bailey Exp $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/11/12 02:25:41 $
 * $Copyright: Copyright (C) 2002 Path Integral Software $
 */
package feynman.framework.controller;

import feynman.framework.simulation.Simulation;
import feynman.framework.simulation.Marshaller;
import feynman.framework.simulation.MarshallingException;
import feynman.framework.system.PhysicalSystemFactory;
import feynman.framework.system.PhysicalSystemFactoryException;
import feynman.framework.system.PhysicalSystem;
import feynman.framework.system.PhysicalConfiguration;
import feynman.framework.system.PhysicalAlgorithm;
import feynman.framework.system.PhysicalMeasurement;
import feynman.framework.system.FinalReport;
import feynman.framework.datastore.DataStoreFactory;
import feynman.framework.datastore.DataStore;
import feynman.framework.datastore.ConnectionException;
import feynman.framework.datastore.InvalidDataStoreException;

/**
 * <p>
 * This class sets up the simulation from the properties file and then runs it
 * based on the configuration classes.  The main method of this class executes
 * the steps of the simulation.  The main method of this class is defined
 * as the executable in the manifest file.  The main steps to running a simulation
 * are as follows:
 * </p>
 * <ol>
 * <li> Write the source for a sub-class of PhysicalObject <em>i.e.</em> develop
 *      a class that sub-classes CartesianObject if you are working in the Cartesian
 *      coordinate system.
 * <li> Write the source classes that implement the <em>PhysicalConfiguration, 
 *      PhysicalAlgorithm, PhysicalMeasurement</em> interfaces.
 * <li> Setup the correct classpath to include the <b>feynman.jar</b> and the
 *      <b>jakarta-regexp-xxx.jar</b> files.
 * <li> Compile the source files you created in steps 1 and 2.
 * <li> Place the generated class files in the same directory as the <b>feynman.jar</b>
 *      file or in a lib or classes sub-directory of the directory containing this file.
 * <li> Run the simulation from the command prompt using the usage below.
 * </ol> 
 * <p>
 * <b>Usage: </b> java -jar feynman.jar [propfile]
 * </p>
 * <p>
 * For a more detailed description see the documentation included with the sample application.
 * </p>
 *
 * @author Wes Bailey
 * @version $Revision: 1.1.1.1 $ $Date: 2002/11/12 02:25:41 $
 */
public class Controller {
	
	// Define the string file name to look for the simulation properties.
	static String propFilename = "Simulation.properties";
	
	public static void main(String [] args) throws ControllerException {
		
		// See if the user defined another properties file to use.
		switch (args.length) {
			case 0:
				// Use default file.
				System.out.println("Using default properties file: " + propFilename);
				break;
			case 1:
				propFilename = args[0];
				System.out.println("Using properties file: " + propFilename);
				break;
			default:
				throw new ControllerException("Usage: java -jar feynman.jar propfile");
		}
		
		// Define the classes that are used to execute the simulation.
		Simulation simulation;
		PhysicalSystem physicalSystem;
		PhysicalConfiguration config;;
		PhysicalAlgorithm physicalAlgorithm;
		PhysicalMeasurement physicalMeasurement;
		FinalReport finalReport = null;
		DataStore dataStore;
		
		// Now create the simulation environment that the user has defined using the
		// appropriate factory methods.
		try {
			
			// Create the simulation bean from the properties file.
			simulation = Marshaller.unmarshall(propFilename);
			
			// Create a new Physical System Factory.
			System.out.print("Creating the physical system...");
			
			PhysicalSystemFactory sf = PhysicalSystemFactory.getInstance();
			physicalSystem = (PhysicalSystem) sf.create(simulation);
			
			System.out.println("created");
			
			// Configure the objects in the physical system.
			System.out.print("Configuring system using <" + simulation.getPhysicalConfigurationClass() + ">...");
			
			Class configurationClazz = Class.forName(simulation.getPhysicalConfigurationClass());
			config = (PhysicalConfiguration) configurationClazz.newInstance();
			config.configure(physicalSystem);
			
			System.out.println("configured");
			
			// Define the algorithm class to be used per iteration on the physicalSystem.
			System.out.print("Configuring Algorithm using <" + simulation.getPhysicalAlgorithmClass() + ">...");
			
			Class algorithmClazz = Class.forName(simulation.getPhysicalAlgorithmClass());
			physicalAlgorithm = (PhysicalAlgorithm) algorithmClazz.newInstance();
			
			System.out.println("configured");
			
			// Define the measurement class to be used on the physical system.
			System.out.print("Configuring Physical Measurement using <" + simulation.getPhysicalMeasurementClass() + ">...");
			
			Class measurementClazz = Class.forName(simulation.getPhysicalMeasurementClass());
			physicalMeasurement = (PhysicalMeasurement) measurementClazz.newInstance();
			
			System.out.println("configured");
			
			// Configure the data store for usage based on the type selected by the user.
			System.out.print("Configuring the Persistent Data Source using <" + simulation.getDataStore() + ">...");
			
			DataStoreFactory dsf = DataStoreFactory.getInstance();
			dataStore = dsf.create(simulation.getDataStore());
			dataStore.open(simulation.getDataStoreFile());
			
			System.out.println("complete");
			
			// Configure the simulation report if there is one defined.
			if (simulation.doFinalReport()) {
				System.out.print("Configuring the FinalReport using <" + simulation.getFinalReportClass() + ">...");
				
				Class reportClazz = Class.forName(simulation.getFinalReportClass());
				finalReport = (FinalReport) reportClazz.newInstance();
				
				System.out.println("complete");
			}
			
		}
		catch (MarshallingException e) {
			throw new ControllerException(e.toString());
		}
		catch (ClassNotFoundException e) {
			throw new ControllerException(e.toString());
		}
		catch (InstantiationException e) {
			throw new ControllerException(e.toString());
		}
		catch (IllegalAccessException e) {
			throw new ControllerException(e.toString());
		}
		catch (PhysicalSystemFactoryException e) {
			throw new ControllerException(e.toString());
		}
		catch (ConnectionException e) {
			throw new ControllerException(e.toString());
		}
		catch (InvalidDataStoreException e) {
			throw new ControllerException(e.toString());
		}
		
		System.out.print("Running simulation...");
		
		// Define references to simulation properties.
		double timeStep = simulation.getInterval();
		boolean performMeasurement = simulation.getPerformMeasurement();
		int numberIterations = simulation.getIterations();
		int iterationsPerMeasurement = numberIterations/simulation.getNumberMeasurements();
		
		// Run the simulation.
		for (int i = 0; i < numberIterations; i++) {
			
			// These calculations are always performed for every iteration.
			physicalAlgorithm.calculate(simulation, physicalSystem);
			
			// Update the time attribute of the simulation bean.
			simulation.setTime(simulation.getTime() + timeStep);
			
			// Exit if the simulation is over before the iterations are completed.
			if (!simulation.isRunning()) {
				try {
					dataStore.close();
				}
				catch (ConnectionException e) {
					throw new ControllerException(e.toString());
				}
				finally {
					System.out.println("complete");
					
					if(simulation.doFinalReport()) {
						finalReport.report(simulation, physicalSystem);
					}
					
					return;
				}
			}
			
			// Test whether or not to take a user defined measurement of
			// the physical system.
			if ((performMeasurement) && ((i % iterationsPerMeasurement) == 0)) {
				
				// Take a user defined measurement.
				physicalMeasurement.take(simulation, physicalSystem);
				
				// Save the measurement to the data store.
				dataStore.save(physicalMeasurement);
				
				//System.out.print(".");
			}
			
		}
		
		// The simulation is complete so wrap it up.
		try {
			dataStore.close();
		}
		catch (ConnectionException e) { 
			throw new ControllerException(e.toString());
		}
		finally {
			System.out.println("complete");
			
			if(simulation.doFinalReport()) {
				finalReport.report(simulation, physicalSystem);
			}
			
			return;
		}
		
	}
	
}
