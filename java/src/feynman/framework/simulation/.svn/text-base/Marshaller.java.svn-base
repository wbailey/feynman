/*
 * $Header: /cvsroot/feynman/src/feynman/framework/simulation/Marshaller.java,v 1.1.1.1 2002/11/12 02:25:41 wesley_bailey Exp $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/11/12 02:25:41 $
 * $Copyright: Copyright (C) 2002 Path Integral Software $
 */
package feynman.framework.simulation;

import org.apache.regexp.RE;
import org.apache.regexp.RESyntaxException;
import java.io.*;
import java.util.*;
import java.lang.reflect.*;

/**
 * Utility class to load the properties file that the user has defined.  If
 * there is a switch to an XML format and using a real Marshalling/Unmarshalling
 * tool like Castor, then this class can easily be refactored to an adaptor class.
 * <p>
 * The constructor is private since this is a utility class so there is no instance
 * of this class to create or get.  To use this class treat it just like the Math
 * utility class in the following manner:
 * <p>
 * <pre>
 * Simulation simulation = Marshaller.unmarshall("Simulation.properties");
 * </pre>
 * </p>
 *
 * @author Wes Bailey
 * @version $Revision: 1.1.1.1 $ $Date: 2002/11/12 02:25:41 $
 */
public class Marshaller {
	
	// Define instance variables.
	private static File file;
	private static FileWriter fw;
	private static FileInputStream fin;
	private static PrintWriter pw;
	private static Properties props;
	
	/**
	 * This is a utility class so there is no instance of the class to be created or
	 * retrieved.
	 */
	private Marshaller() {
		// utility class
	}
	
	/**
	 * Method to save a serialized version of the simulation object.
	 *
	 * @param sim The simulation bean to serialize.
	 * @param outfile The file to save the contents of the bean to.
	 */
	public static void marshall(Simulation sim, String outfile) throws MarshallingException {
		
		try {
			file = new File(outfile);
			fw = new FileWriter(file);
			pw = new PrintWriter(fw);
		
			pw.println(sim.toString());
		
			pw.close();
			fw.close();
		}
		catch (IOException e) {
			throw new MarshallingException(e.toString());
		}
		
	}
	
	/**
	 * Method to create a simulation object with attribute values specified by the
	 * properties file description of the object.
	 *
	 * @param infile The name of the properties file to parse and create the bean from.
	 */
	public static Simulation unmarshall(String infile) throws MarshallingException {
		
		// The simulation is a singleton class.
		Simulation sim = Simulation.getInstance();
		
		// Prepare for reflection operations to invoke the correct methods from the
		// properties file.
		Method [] methods = sim.getClass().getMethods();
		
		try {
			
			// Define the properties file used to define the simulation bean
			file = new File(infile);
			fin = new FileInputStream(file);
			
			// Create the properties based on the file
			props = new Properties();
			props.load(fin);
			
			/*
			 * For debugging...
			for (Enumeration e = props.propertyNames(); e.hasMoreElements(); ) {
				String name = (String) e.nextElement();
				System.out.println("name: " + name + "\t value: " + props.getProperty(name));
			}
			*/
			
			// Setup validation regular expressions.
			RE stringRegexp;
			RE intRegexp;
			RE decimalRegexp;
			RE booleanRegexp;
			try {
				stringRegexp = new RE("^[a-zA-Z\\.]*$");
				intRegexp = new RE("^[0-9]*$");
				decimalRegexp = new RE("^[0-9]*\\.[0-9]*$");
				booleanRegexp = new RE("^(true|false)$");
			}
			catch (RESyntaxException e) {
				throw new MarshallingException("Please report the following error as a bug report: " + e.toString());
			}
			
			// Create the array to be used in the method.invoke(Object obj, Object [] objs)
			Object [] invokeParam = new Object[1]; 
			
			// For each method in the array, examine and determine if we have a setter
			// method.  If we do then load the appropriate value from the properties file.
			for (int i=0; i<methods.length; i++) {
				
				// Work with the method object as the loop, and not the properties.  Make it
				// easier later when we want to invoke the actual method.
				Method method = methods[i];
				
				// Catch on the setter methods.  They start with the string set and
				// have only one parameter.
				if (method.getName().startsWith("set")) {
					
					// Check the documentation for the Class object if this doesn't make
					// sense to you.
					Class [] params = method.getParameterTypes();
					
					if (params.length == 1) {
						
						// Should be obvious what we are capturing here.
						Class param = params[0];
						String paramType = param.getName();
						String propName = method.getName().substring(3);
						String propValue = props.getProperty(propName);
						
						/*
						 * Test each based on the parameter type.  If there is a property 
						 * that is assigned, then test if the value is in the correct format
						 * using the regular expressions to test validity.  If they are valid,
						 * then invoke the setter method for the property on the Simulation sim
						 * object with the appropriate parameter array.  Throw a marshalling
						 * exception with more information to the user on the invalid property
						 * otherwise.
						 */
						if (!(propValue == null)) {
							if (paramType.equals("int")) {
								if(intRegexp.match(propValue)) {
									invokeParam[0] = new Integer(propValue);
									method.invoke(sim, invokeParam);
								} else {
									throw new MarshallingException("Invalid " + propName + " value: " + propValue);
								}
							} else if (paramType.equals("double")) {
								if (decimalRegexp.match(propValue)) {
									invokeParam[0] = new Double(propValue);
									method.invoke(sim, invokeParam);
								} else {
									throw new MarshallingException("Invalid " + propName + " value: " + propValue);
								}
							} else if (paramType.equals("java.lang.String")) {
								if (stringRegexp.match(propValue)) {
									invokeParam[0] = propValue;
									method.invoke(sim, invokeParam);
								} else {
									throw new MarshallingException("Invalid " + propName + " value: " + propValue);
								}
							} else if (paramType.equals("boolean")) {
								if (booleanRegexp.match(propValue)) {
									invokeParam[0] = new Boolean(propValue);
									method.invoke(sim, invokeParam);
								} else {
									throw new MarshallingException("Invalid " + propName + " value: " + propValue);
								}
							}
						}
					}
				}
			}
			
			// Close up the properties file input stream
			fin.close();
			
			// Return the constructed bean.
			return sim;
		
		}
		catch (IllegalAccessException e) {
			throw new MarshallingException("Can't access property: " + e.toString());
		}
		catch (InvocationTargetException e) {
			throw new MarshallingException("Invalid property: " + e.toString());
		}
		catch (FileNotFoundException e) {
			throw new MarshallingException("Invalid File: " + file + " " + e.toString());
		}
		catch (IOException e) {
			throw new MarshallingException("Problem File: " + file + " " + e.toString());
		}
		
	}
	
}
