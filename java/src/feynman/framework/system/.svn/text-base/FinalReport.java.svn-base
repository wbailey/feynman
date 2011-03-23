/*
 * $Header: /cvsroot/feynman/src/feynman/framework/system/FinalReport.java,v 1.1.1.1 2002/11/12 02:25:43 wesley_bailey Exp $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/11/12 02:25:43 $
 * $Copyright: Copyright (C) 2002 Wes Bailey, Oakland, CA, USA $
 */
package feynman.framework.system;

import feynman.framework.simulation.Simulation;

/**
 * This interface defines a simple way of reporting final statistics or calculations
 * that occured in the simulation.  To define the usage of a FinalReport implement 
 * the following in the <em>Simulation.properties</em> file in the following manner:
 * <p>
 * <pre>
 * FinalReportClass=Report
 * DoFinalReport=true
 * </pre>
 *
 * @author Wes Bailey
 * @version $Revision: 1.1.1.1 $ $Date: 2002/11/12 02:25:43 $
 */
public interface FinalReport {
	
	/**
	 * Use this method to write any final data or calculation to <em>stdout</em>
	 * for the user of the simulation.
	 */
	public void report(Simulation sim, PhysicalSystem  ps);
	
}
