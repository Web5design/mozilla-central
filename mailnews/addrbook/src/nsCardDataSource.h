/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.0 (the "NPL"); you may not use this file except in
 * compliance with the NPL.  You may obtain a copy of the NPL at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the NPL is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the NPL
 * for the specific language governing rights and limitations under the
 * NPL.
 *
 * The Initial Developer of this code under the NPL is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1999 Netscape Communications Corporation.  All Rights
 * Reserved.
 */

#include "nsCOMPtr.h"
#include "nsIRDFDataSource.h"
#include "nsIRDFService.h"
#include "nsIAbListener.h"
#include "nsIAbCard.h"
#include "nsISupportsArray.h"


/**
 * The addressbook person card data source.
 */
class nsABCardDataSource : public nsIRDFDataSource,
						 public nsIAbListener
{
private:
	nsCOMPtr<nsISupportsArray> mObservers;
	PRBool		mInitialized;

	// The cached service managers

	nsIRDFService* mRDFService;
  
public:
  
	NS_DECL_ISUPPORTS

	nsABCardDataSource(void);
	virtual ~nsABCardDataSource (void);
	nsresult Init();

	// nsIRDFDataSource methods

	NS_IMETHOD GetURI(char* *uri);

	NS_IMETHOD GetSource(nsIRDFResource* property,
					   nsIRDFNode* target,
					   PRBool tv,
					   nsIRDFResource** source /* out */);

	NS_IMETHOD GetTarget(nsIRDFResource* source,
					   nsIRDFResource* property,
					   PRBool tv,
					   nsIRDFNode** target);

	NS_IMETHOD GetSources(nsIRDFResource* property,
						nsIRDFNode* target,
						PRBool tv,
						nsISimpleEnumerator** sources);

	NS_IMETHOD GetTargets(nsIRDFResource* source,
						nsIRDFResource* property,    
						PRBool tv,
						nsISimpleEnumerator** targets);

	NS_IMETHOD Assert(nsIRDFResource* source,
					nsIRDFResource* property, 
					nsIRDFNode* target,
					PRBool tv);

	NS_IMETHOD Unassert(nsIRDFResource* source,
					  nsIRDFResource* property,
					  nsIRDFNode* target);

  NS_IMETHOD Change(nsIRDFResource *aSource,
                    nsIRDFResource *aProperty,
                    nsIRDFNode *aOldTarget,
                    nsIRDFNode *aNewTarget);

  NS_IMETHOD Move(nsIRDFResource *aOldSource,
                  nsIRDFResource *aNewSource,
                  nsIRDFResource *aProperty,
                  nsIRDFNode *aTarget);

	NS_IMETHOD HasAssertion(nsIRDFResource* source,
						  nsIRDFResource* property,
						  nsIRDFNode* target,
						  PRBool tv,
						  PRBool* hasAssertion);

	NS_IMETHOD AddObserver(nsIRDFObserver* n);

	NS_IMETHOD RemoveObserver(nsIRDFObserver* n);

	NS_IMETHOD ArcLabelsIn(nsIRDFNode* node,
						 nsISimpleEnumerator** labels);

	NS_IMETHOD ArcLabelsOut(nsIRDFResource* source,
						  nsISimpleEnumerator** labels); 

	NS_IMETHOD GetAllResources(nsISimpleEnumerator** aCursor);

	NS_IMETHOD GetAllCommands(nsIRDFResource* source,
							nsIEnumerator/*<nsIRDFResource>*/** commands);

	NS_IMETHOD IsCommandEnabled(nsISupportsArray/*<nsIRDFResource>*/* aSources,
							  nsIRDFResource*   aCommand,
							  nsISupportsArray/*<nsIRDFResource>*/* aArguments,
							  PRBool* aResult);

	NS_IMETHOD DoCommand(nsISupportsArray/*<nsIRDFResource>*/* aSources,
					   nsIRDFResource*   aCommand,
					   nsISupportsArray/*<nsIRDFResource>*/* aArguments);

	NS_IMETHOD OnItemAdded(nsIAbBase *parentDirectory, nsISupports *item);

	NS_IMETHOD OnItemRemoved(nsIAbBase *parentDirectory, nsISupports *item);

	NS_IMETHOD OnItemPropertyChanged(nsISupports *item, const char *property,
									const char *oldValue, const char *newValue);

  // caching frequently used resources
protected:

	void createNode(nsString& str, nsIRDFNode **node);
	void createNode(PRUint32 value, nsIRDFNode **node);
	nsresult NotifyPropertyChanged(nsIRDFResource *resource, nsIRDFResource *propertyResource,
									const char *oldValue, const char *newValue);

	nsresult NotifyObservers(nsIRDFResource *subject, nsIRDFResource *property,
							nsIRDFNode *object, PRBool assert);
	nsresult createCardNode(nsIAbCard* directory, nsIRDFResource* property,
                            nsIRDFNode** target);
	static nsresult getCardArcLabelsOut(nsIAbCard *directory,
										nsISupportsArray **arcs);

	nsresult DoDeleteFromCard(nsIAbCard *directory,
							  nsISupportsArray *arguments);

	nsresult DoNewCard(nsIAbCard *directory,
							  nsISupportsArray *arguments);

	static PRBool assertEnumFunc(nsISupports *aElement, void *aData);
	static PRBool unassertEnumFunc(nsISupports *aElement, void *aData);

	static nsIRDFResource* kNC_PersonName;
	static nsIRDFResource* kNC_ListName;
	static nsIRDFResource* kNC_Email;
	static nsIRDFResource* kNC_City;
	static nsIRDFResource* kNC_Organization;
	static nsIRDFResource* kNC_WorkPhone;
	static nsIRDFResource* kNC_Nickname;

	// commands
	static nsIRDFResource* kNC_Delete;
	static nsIRDFResource* kNC_NewCard;

};
