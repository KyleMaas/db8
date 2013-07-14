/* @@@LICENSE
*
*      Copyright (c) 2009-2012 Hewlett-Packard Development Company, L.P.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* LICENSE@@@ */


#ifndef MOJNOCOPY_H_
#define MOJNOCOPY_H_

/**
 * Prevent class from being copied
 *
 * Defines both common methods of copying a class as private members to prevent
 * instances of any derivative class from being copied.
 */
class MojNoCopy
{
protected:
	/**
	 * Allow a regular constructor
	 *
	 * The normal constructor is defined as protected to allow it to be
	 * called by derivative classes.  This class, however, is prevented from
	 * being instantiated directly and is thereby only allowed to be used
	 * by a derivative class.
	 */
	MojNoCopy() {}

private:
	/**
	 * Copy constructor
	 *
	 * Defined as private to disallow copying of instances via the copy
	 * constructor.
	 *
	 * @param	instance		Reference to instance to copy.
	 */
	MojNoCopy(const MojNoCopy&);

	/**
	 * Assignment operator
	 *
	 * Defined as private to disallow copying of instances via a simple
	 * variable assignment.
	 * 
	 * @param	instance		Reference to instance to copy.
	 */
	MojNoCopy& operator=(const MojNoCopy&);
};

#endif /* MOJNOCOPY_H_ */
