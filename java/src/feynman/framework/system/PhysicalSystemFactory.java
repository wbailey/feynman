/*
 * $Header: /cvsroot/feynman/src/feynman/framework/system/PhysicalSystemFactory.java,v 1.1.1.1 2002/11/12 02:25:43 wesley_bailey Exp $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/11/12 02:25:43 $
 * $Copyright: Copyright (C) 2002 Wes Bailey, Oakland, CA, USA $
 */
package feynman.framework.system;

import java.lang.reflect.Method;
import java.lang.reflect.InvocationTargetException;
import feynman.framework.simulation.Simulation;

/**
 * Factory to create differenct types of <b>PhysicalSystems</b>.
 *
 * @author Wes Bailey
 * @version $Revision: 1.1.1.1 $ $Date: 2002/11/12 02:25:43 $
 */
public class PhysicalSystemFactory {
	
	// Create and instance of the class.
	private static final PhysicalSystemFactory INSTANCE = new PhysicalSystemFactory();
	
	private PhysicalSystemFactory() {
		// singleton
	}
	
	/**
	 * Method used to retrieve an instance of the factory class.
	 */
	public static final PhysicalSystemFactory getInstance() {
		return INSTANCE;
	}
	
	/**
	 * <b>Note:</b> This method is used by the <em>feynman.framework.Controller</em>.
	 * Unless you are not using those classes to build your simulation, you should 
	 * not have to use this factory class directly.  If you do, then follow the 
	 * instructions given below.
	 * <p/>
	 * Use this method to create a <b>PhysicalSystem</b> of <b>PhysicalObjects</b>.
	 * The <em>className</em> is the name of the class to be instantiated for the
	 * type of physical system to be created.  For example, if the client wants to
	 * to create a system included in the framework, then the following call to this
	 * factory will work:
	 * <p>
	 * <pre>
	 * Simulation simulation = Marshaller.unmarshall("MyProps.properties");
	 * PhysicalSystemFactory sf = PhysicalSystemFactory.getInstance();
	 * PhysicalSystem ps = sf.create(simulation);
	 * </pre>
	 */
	public static PhysicalSystem create(Simulation simulation) throws PhysicalSystemFactoryException {
		
		try {
			
			// Create the system specified for study in the simulation bean.
			Class psClazz = Class.forName(simulation.getPhysicalSystemClass());
			PhysicalSystem ps = (PhysicalSystem) psClazz.newInstance();
			
			// Get the number of physical objects for the simulation.
			int numberPhysicalObjects = simulation.getNumberPhysicalObjects();
			
			// Get the factory for the Physical Objects.
			Class ofClazz = Class.forName(simulation.getPhysicalObjectFactoryClass());
			Method method = ofClazz.getMethod("getInstance", new Class [] { });
			PhysicalObjectFactory of = (PhysicalObjectFactory) method.invoke(null, null);
			
			// Create the objects and add them to the system.
			PhysicalObject po;
			
			for (int i=0; i < numberPhysicalObjects; i++) {
				
				try {
					
					po = (PhysicalObject) of.create(simulation);
					
					if (!(ps.add(po))) {
						throw new PhysicalSystemFactoryException("Attempting to add " + ofClazz.getName() + " that is not a valid type for the " + psClazz.getName());
					}
					
				}
				catch (PhysicalObjectFactoryException e) {
					throw new PhysicalSystemFactoryException(e.toString());
				}
				
			}
			
			return ps;
			
		}
		catch (ClassNotFoundException e) {
			throw new PhysicalSystemFactoryException(e.toString());
		}
		catch (InstantiationException e) {
			throw new PhysicalSystemFactoryException(e.toString());
		}
		catch (IllegalAccessException e) {
			throw new PhysicalSystemFactoryException(e.toString());
		}
		catch (NoSuchMethodException e) {
			throw new PhysicalSystemFactoryException(e.toString());
		}
		catch (InvocationTargetException e) {
			throw new PhysicalSystemFactoryException(e.toString());
		}
		
	}
	
}
