/*
 * $Header: /cvsroot/feynman/src/feynman/framework/system/PhysicalObjectFactory.java,v 1.1.1.1 2002/11/12 02:25:43 wesley_bailey Exp $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/11/12 02:25:43 $
 * $Copyright: Copyright (C) 2002 Wes Bailey, Oakland, CA, USA $
 */
package feynman.framework.system;

import feynman.framework.simulation.*;
/**
 * Factory to define the creation of Physical Objects to be used
 * in the system of study.  The sub-class will instantiate all
 * objects that are used in the system.
 * <p>
 * Example: CartesianObjectFactory creates CartesianParticle.
 *
 * @author Wes Bailey
 * @version $Revision: 1.1.1.1 $ $Date: 2002/11/12 02:25:43 $
 */
public interface PhysicalObjectFactory {

	// Used to generate a particle for the system of study.
	public PhysicalObject create(Simulation simulation) throws PhysicalObjectFactoryException;

}
