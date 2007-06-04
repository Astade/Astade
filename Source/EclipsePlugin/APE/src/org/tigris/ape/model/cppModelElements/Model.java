/**
 * 
 */
package org.tigris.ape.model.cppModelElements;

import org.apache.log4j.Logger;
import org.tigris.ape.model.genericModelElements.DirectoryElement;

/**
 * @author Tobias Zipfel
 *
 */
public class Model extends DirectoryElement {
	
	static Logger logger = Logger.getLogger(Model.class.getName());

	public Model(String pathName) {
		super(pathName);
	}
}
