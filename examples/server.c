/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information. */

/**
 * Working with Objects and Object Types
 * -------------------------------------
 *
 * Using objects to structure information models
 * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 * Assume a situation where we want to model a set of pumps and their runtime
 * state in an OPC UA information model. Of course, all pump representations
 * should follow the same basic structure, For example, we might have graphical
 * representation of pumps in a SCADA visualisation that shall be resuable for
 * all pumps.
 *
 * Following the object-oriented programming paradigm, every pump is represented
 * by an object with the following layout:
 *
 * .. graphviz::
 *
 *    digraph tree {
 *
 *    fixedsize=true;
 *    node [width=2, height=0, shape=box, fillcolor="#E5E5E5", concentrate=true]
 *
 *    node_root [label=< <I>ObjectNode</I><BR/>Pump >]
 *
 *    { rank=same
 *      point_1 [shape=point]
 *      node_1 [label=< <I>VariableNode</I><BR/>ManufacturerName >] }
 *    node_root -> point_1 [arrowhead=none]
 *    point_1 -> node_1 [label="hasComponent"]
 *
 *    { rank=same
 *      point_2 [shape=point]
 *      node_2 [label=< <I>VariableNode</I><BR/>ModelName >] }
 *    point_1 -> point_2 [arrowhead=none]
 *    point_2 -> node_2 [label="hasComponent"]
 *
 *    {  rank=same
 *       point_4 [shape=point]
 *       node_4 [label=< <I>VariableNode</I><BR/>Status >] }
 *    point_2 -> point_4 [arrowhead=none]
 *    point_4 -> node_4 [label="hasComponent"]
 *
 *    {  rank=same
 *       point_5 [shape=point]
 *       node_5 [label=< <I>VariableNode</I><BR/>MotorRPM >] }
 *    point_4 -> point_5 [arrowhead=none]
 *    point_5 -> node_5 [label="hasComponent"]
 *
 *    }
 *
 * The following code manually defines a pump and its member variables. We omit
 * setting constraints on the variable values as this is not the focus of this
 * tutorial and was already covered. */

#include <open62541/plugin/log_stdout.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>

#include <signal.h>

static UA_NodeId
manuallyDefineBat40(UA_Server *server) {
    UA_NodeId batId; /* get the nodeid assigned by the server */
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Batiment_40");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "Batiment_40"), UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &batId);

    UA_VariableAttributes alarmAttr = UA_VariableAttributes_default;
    UA_Boolean alarmValue = true;
    UA_Variant_setScalar(&alarmAttr.value, &alarmValue, &UA_TYPES[UA_TYPES_BOOLEAN]);
    alarmAttr.displayName = UA_LOCALIZEDTEXT("en-US", "AlarmeIncendie");
    alarmAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, batId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "AlarmeIncendie"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), alarmAttr, NULL, NULL);

    UA_VariableAttributes automatBit2VieAttr = UA_VariableAttributes_default;
    UA_Boolean automatBit2VieValue = true;
    UA_Variant_setScalar(&automatBit2VieAttr.value, &automatBit2VieValue, &UA_TYPES[UA_TYPES_BOOLEAN]);
    automatBit2VieAttr.displayName = UA_LOCALIZEDTEXT("en-US", "AutomateBit2Vie");
    automatBit2VieAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, batId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "AutomateBit2Vie"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), automatBit2VieAttr, NULL, NULL);

    UA_VariableAttributes etatInstallationAttr = UA_VariableAttributes_default;
    UA_Int32 etatInstallationValue = 0;
    UA_Variant_setScalar(&etatInstallationAttr.value, &etatInstallationValue, &UA_TYPES[UA_TYPES_INT32]);
    etatInstallationAttr.displayName = UA_LOCALIZEDTEXT("en-US", "EtatInstallation");
    etatInstallationAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, batId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "EtatInstallation"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), etatInstallationAttr, NULL, NULL);

    UA_VariableAttributes modeVidageAttr = UA_VariableAttributes_default;
    UA_Boolean modeVidageValue = true;
    UA_Variant_setScalar(&automatBit2VieAttr.value, &modeVidageValue, &UA_TYPES[UA_TYPES_BOOLEAN]);
    automatBit2VieAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ModeVidage");
    automatBit2VieAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, batId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "ModeVidage"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), automatBit2VieAttr, NULL, NULL);
    return batId;
}

/**
 * Object types, type hierarchies and instantiation
 * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 * Building up each object manually requires us to write a lot of code.
 * Furthermore, there is no way for clients to detect that an object represents
 * a pump. (We might use naming conventions or similar to detect pumps. But
 * that's not exactly a clean solution.) Furthermore, we might have more devices
 * than just pumps. And we require all devices to share some common structure.
 * The solution is to define ObjectTypes in a hierarchy with inheritance
 * relations.
 *
 * .. graphviz::
 *
 *    digraph tree {
 *
 *    fixedsize=true;
 *    node [width=2, height=0, shape=box, fillcolor="#E5E5E5", concentrate=true]
 *
 *    node_root [label=< <I>ObjectTypeNode</I><BR/>Device >]
 *
 *    { rank=same
 *      point_1 [shape=point]
 *      node_1 [label=< <I>VariableNode</I><BR/>ManufacturerName<BR/>(mandatory) >] }
 *    node_root -> point_1 [arrowhead=none]
 *    point_1 -> node_1 [label="hasComponent"]
 *
 *    { rank=same
 *      point_2 [shape=point]
 *      node_2 [label=< <I>VariableNode</I><BR/>ModelName >] }
 *    point_1 -> point_2 [arrowhead=none]
 *    point_2 -> node_2 [label="hasComponent"]
 *
 *    {  rank=same
 *       point_3 [shape=point]
 *       node_3 [label=< <I>ObjectTypeNode</I><BR/>Pump >] }
 *    point_2 -> point_3 [arrowhead=none]
 *    point_3 -> node_3 [label="hasSubtype"]
 *
 *    {  rank=same
 *       point_4 [shape=point]
 *       node_4 [label=< <I>VariableNode</I><BR/>Status<BR/>(mandatory) >] }
 *    node_3 -> point_4 [arrowhead=none]
 *    point_4 -> node_4 [label="hasComponent"]
 *
 *    {  rank=same
 *       point_5 [shape=point]
 *       node_5 [label=< <I>VariableNode</I><BR/>MotorRPM >] }
 *    point_4 -> point_5 [arrowhead=none]
 *    point_5 -> node_5 [label="hasComponent"]
 *
 *    }
 *
 * Children that are marked mandatory are automatically instantiated together
 * with the parent object. This is indicated by a `hasModellingRule` reference
 * to an object that representes the `mandatory` modelling rule. */

/* predefined identifier for later use */
UA_NodeId gareTypeId = {1, UA_NODEIDTYPE_NUMERIC, {1005}};
UA_NodeId missionDataTypeId = {1, UA_NODEIDTYPE_NUMERIC, {1006}};
UA_NodeId garesTypeId = {1, UA_NODEIDTYPE_NUMERIC, {1003}};
UA_NodeId missionTypeId = {1, UA_NODEIDTYPE_NUMERIC, {1004}};
UA_NodeId zonesTypeId = {1, UA_NODEIDTYPE_NUMERIC, {1001}};
UA_NodeId zoneTypeId = {1, UA_NODEIDTYPE_NUMERIC, {1002}};

static void
defineObjectTypesGare(UA_Server *server) {
    /* Define the object type for "Gare" */
    UA_NodeId gareId; /* get the nodeid assigned by the server */
    UA_ObjectTypeAttributes gareTypeAttr = UA_ObjectTypeAttributes_default;
    gareTypeAttr.displayName = UA_LOCALIZEDTEXT("en-US", "GareType");
    UA_Server_addObjectTypeNode(server, UA_NODEID_NULL,
                                UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                                UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(1, "GareType"), gareTypeAttr,
                                NULL, &gareId);

    UA_VariableAttributes contenuAttr = UA_VariableAttributes_default;
    contenuAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Contenu");
    contenuAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_NodeId contenuId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, gareId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "Contenu"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), contenuAttr, NULL, &contenuId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, contenuId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);


    UA_VariableAttributes etatAttr = UA_VariableAttributes_default;
    etatAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Etat");
    etatAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_NodeId etatId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, gareId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "Etat"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), etatAttr, NULL, &etatId);
    /* Make the etat mandatory */
    UA_Server_addReference(server, etatId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
   

    UA_VariableAttributes etatBalAttr = UA_VariableAttributes_default;
    etatBalAttr.displayName = UA_LOCALIZEDTEXT("en-US", "EtatBalancelle");
    etatBalAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_NodeId etatBalId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, gareId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "EtatBalancelle"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), etatBalAttr, NULL, &etatBalId);
    /* Make the etat mandatory */
    UA_Server_addReference(server, etatBalId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
    
    UA_VariableAttributes messageAttr = UA_VariableAttributes_default;
    messageAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Message");
    messageAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_NodeId messageId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, gareId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "Message"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), messageAttr, NULL, &messageId);
    /* Make the etat mandatory */
   UA_Server_addReference(server, messageId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
  
   /* Define the object type for "Gare" */
    UA_ObjectTypeAttributes gtAttr = UA_ObjectTypeAttributes_default;
    gtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "GareType");
    UA_Server_addObjectTypeNode(server, gareTypeId,
                                gareId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(1, "GareType"), gtAttr,
                                NULL, NULL);

    
}

static void
defineObjectTypesGares(UA_Server *server) {
    /* Define the object type for "Gares" */
    UA_NodeId garesId; /* get the nodeid assigned by the server */
    UA_ObjectTypeAttributes garesTypeAttr = UA_ObjectTypeAttributes_default;
    garesTypeAttr.displayName = UA_LOCALIZEDTEXT("en-US", "GaresType");
    UA_Server_addObjectTypeNode(server, UA_NODEID_NULL,
                                UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                                UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(1, "GaresType"), garesTypeAttr,
                                NULL, &garesId);
    
       // Define the object type for "Gare" 
    UA_ObjectTypeAttributes gtAttr = UA_ObjectTypeAttributes_default;
    gtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "GaresType");
    UA_Server_addObjectTypeNode(server, garesTypeId,
                                garesId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(1, "GaresType"), gtAttr,
                                NULL, NULL);
    
}


static void
defineObjectTypesMissionData(UA_Server *server) {
    /* Define the object type for "Gare" */
    UA_NodeId missionDataId; /* get the nodeid assigned by the server */
    UA_ObjectTypeAttributes missionDataTypeAttr = UA_ObjectTypeAttributes_default;
    missionDataTypeAttr.displayName = UA_LOCALIZEDTEXT("en-US", "MissionDataType");
    UA_Server_addObjectTypeNode(server, UA_NODEID_NULL,
                                UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                                UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(1, "MissionData"), missionDataTypeAttr,
                                NULL, &missionDataId);

    UA_VariableAttributes ackPanoAttr = UA_VariableAttributes_default;
    ackPanoAttr.displayName = UA_LOCALIZEDTEXT("en-US", "AckPano");
    ackPanoAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_NodeId ackPanoId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, missionDataId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "AckPano"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), ackPanoAttr, NULL, &ackPanoId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, ackPanoId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);


    UA_VariableAttributes indiceGareAttr = UA_VariableAttributes_default;
    indiceGareAttr.displayName = UA_LOCALIZEDTEXT("en-US", "IndiceGare");
    indiceGareAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_NodeId indiceGareId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, missionDataId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "IndiceGare"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), indiceGareAttr, NULL, &indiceGareId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, indiceGareId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
   

    UA_VariableAttributes requeteAttr = UA_VariableAttributes_default;
    requeteAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Requete");
    requeteAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_NodeId requeteId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, missionDataId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "Requete"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), requeteAttr, NULL, &requeteId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, requeteId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
    
    UA_VariableAttributes typeAttr = UA_VariableAttributes_default;
    typeAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Type");
    typeAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_NodeId typeId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, missionDataId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "Type"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), typeAttr, NULL, &typeId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, typeId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
  
   
    /* Define the object type for "Pump" */
    UA_ObjectTypeAttributes mdtAttr = UA_ObjectTypeAttributes_default;
    mdtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "MissionDataType");
    UA_Server_addObjectTypeNode(server, missionDataTypeId,
                                missionDataId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(1, "MissionDataType"), mdtAttr,
                                NULL, NULL);
    
}


static void
defineObjectTypesMission(UA_Server *server) {
    /* Define the object type for "Mission" */
    UA_NodeId missionId; /* get the nodeid assigned by the server */
    UA_ObjectTypeAttributes missionTypeAttr = UA_ObjectTypeAttributes_default;
    missionTypeAttr.displayName = UA_LOCALIZEDTEXT("en-US", "MissionType");
    UA_Server_addObjectTypeNode(server, UA_NODEID_NULL,
                                UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                                UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(1, "MissionType"), missionTypeAttr,
                                NULL, &missionId);

    
       // Define the object type for "Gare" 
    UA_ObjectTypeAttributes gtAttr = UA_ObjectTypeAttributes_default;
    gtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "MissionType");
    UA_Server_addObjectTypeNode(server, missionTypeId,
                                missionId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(1, "MissionType"), gtAttr,
                                NULL, NULL);
    
}

// Zones : liste de plusieurs zones
static void
defineObjectTypesZones(UA_Server *server) {
    /* Define the object type for "Zones" */
    UA_NodeId zonesId; /* get the nodeid assigned by the server */
    UA_ObjectTypeAttributes zonesTypeAttr = UA_ObjectTypeAttributes_default;
    zonesTypeAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ZonesType");
    UA_Server_addObjectTypeNode(server, UA_NODEID_NULL,
                                UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                                UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(1, "ZonesType"), zonesTypeAttr,
                                NULL, &zonesId);

    
    // Define the object type for "Zones" 
    UA_ObjectTypeAttributes zstAttr = UA_ObjectTypeAttributes_default;
    zstAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ZonesType");
    UA_Server_addObjectTypeNode(server, zonesTypeId,
                                zonesId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(1, "ZonesType"), zstAttr,
                                NULL, NULL);
    
}

// Zone : ie. Z1 etc..
static void
defineObjectTypesZone(UA_Server *server) {
    /* Define the object type for "Zone" */
    UA_NodeId zoneId; /* get the nodeid assigned by the server */
    UA_ObjectTypeAttributes zoneTypeAttr = UA_ObjectTypeAttributes_default;
    zoneTypeAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ZoneType");
    UA_Server_addObjectTypeNode(server, UA_NODEID_NULL,
                                UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                                UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(1, "ZoneType"), zoneTypeAttr,
                                NULL, &zoneId);

    
    // Define the object type for "Zone" 
    UA_ObjectTypeAttributes ztAttr = UA_ObjectTypeAttributes_default;
    ztAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ZoneType");
    UA_Server_addObjectTypeNode(server, zoneTypeId,
                                zoneId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(1, "ZoneType"), ztAttr,
                                NULL, NULL);
    
}

/**
 * Now we add the derived ObjectType for the pump that inherits from the device
 * object type. The resulting object contains all mandatory child variables.
 * These are simply copied over from the object type. The object has a reference
 * of type ``hasTypeDefinition`` to the object type, so that clients can detect
 * the type-instance relation at runtime.
 */

static void
addGareObjectInstance(UA_Server *server, char *name, UA_NodeId idToInsert) {
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", name);
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            idToInsert,//UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, name),
                            gareTypeId, /* this refers to the object type
                                           identifier */
                            oAttr, NULL, NULL);
}

static UA_NodeId
addGaresObjectInstance(UA_Server *server, char *name, UA_NodeId idToInsert) {
    UA_NodeId refGaresTypeId;
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", name);
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            idToInsert,//UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, name),
                            garesTypeId, /* this refers to the object type
                                           identifier */
                            oAttr, NULL, &refGaresTypeId);
    return refGaresTypeId;
}


static void
addMissionDataObjectInstance(UA_Server *server, char *name, UA_NodeId idToInsert) {
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", name);
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            idToInsert,//UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, name),
                            missionDataTypeId, /* this refers to the object type
                                           identifier */
                            oAttr, NULL, NULL);
}

static UA_NodeId
addMissionObjectInstance(UA_Server *server, char *name, UA_NodeId idToInsert) {
    UA_NodeId refMissionTypeId;
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", name);
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            idToInsert,//UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, name),
                            missionTypeId, /* this refers to the object type
                                           identifier */
                            oAttr, NULL, &refMissionTypeId);
    return refMissionTypeId;
}

static UA_NodeId
addZonesObjectInstance(UA_Server *server, char *name, UA_NodeId idToInsert) {
    UA_NodeId refZonesTypeId;
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", name);
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            idToInsert,//UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, name),
                            zonesTypeId, /* this refers to the object type
                                           identifier */
                            oAttr, NULL, &refZonesTypeId);
    return refZonesTypeId;
}

static UA_NodeId
addZoneObjectInstance(UA_Server *server, char *name, UA_NodeId idToInsert) {
    UA_NodeId refZoneTypeId;
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", name);
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            idToInsert,//UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, name),
                            zoneTypeId, /* this refers to the object type
                                           identifier */
                            oAttr, NULL, &refZoneTypeId);
    return refZoneTypeId;
}

/**
 * Often we want to run a constructor function on a new object. This is
 * especially useful when an object is instantiated at runtime (with the
 * AddNodes service) and the integration with an underlying process cannot be
 * manually defined. In the following constructor example, we simply set the
 * pump status to on.
 */

static UA_StatusCode
gareTypeConstructor(UA_Server *server,
                    const UA_NodeId *sessionId, void *sessionContext,
                    const UA_NodeId *typeId, void *typeContext,
                    const UA_NodeId *nodeId, void **nodeContext) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "New gare created");

    /* Find the NodeId of the status child variable */
    UA_RelativePathElement rpe;
    UA_RelativePathElement_init(&rpe);
    rpe.referenceTypeId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT);
    rpe.isInverse = false;
    rpe.includeSubtypes = false;
    rpe.targetName = UA_QUALIFIEDNAME(1, "Contenu");

    UA_BrowsePath bp;
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;

    UA_BrowsePathResult bpr =
        UA_Server_translateBrowsePathToNodeIds(server, &bp);
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;

    /* Set the status value */
    UA_Int32 contenue = 0;
    UA_Variant contenueValue;
    UA_Variant_setScalar(&contenueValue, &contenue, &UA_TYPES[UA_TYPES_INT32]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, contenueValue);
    UA_BrowsePathResult_clear(&bpr);

    /*find etat*/
    rpe.targetName = UA_QUALIFIEDNAME(1, "Etat");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;
    
    /* Set the etat value */
    UA_Int32 etat = 0;
    UA_Variant etatValue;
    UA_Variant_setScalar(&etatValue, &etat, &UA_TYPES[UA_TYPES_INT32]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, etatValue);
    UA_BrowsePathResult_clear(&bpr);
    
    /*find etat balancelle*/
    rpe.targetName = UA_QUALIFIEDNAME(1, "EtatBalancelle");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;
        
    /* Set the etat balancelle value */
    UA_Int32 etatBal = 0;
    UA_Variant etatBalValue;
    UA_Variant_setScalar(&etatBalValue, &etatBal, &UA_TYPES[UA_TYPES_INT32]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, etatBalValue);
    UA_BrowsePathResult_clear(&bpr);
    
    
    /*find message*/
    rpe.targetName = UA_QUALIFIEDNAME(1, "Message");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;
        
    /* Set the message value */
    UA_String message = UA_STRING("- RAS -");
    UA_Variant messageValue;
    UA_Variant_setScalar(&messageValue, &message, &UA_TYPES[UA_TYPES_STRING]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, messageValue);
    UA_BrowsePathResult_clear(&bpr);
    /* At this point we could replace the node context .. */

    return UA_STATUSCODE_GOOD;
}



static UA_StatusCode
missionDataTypeConstructor(UA_Server *server,
                    const UA_NodeId *sessionId, void *sessionContext,
                    const UA_NodeId *typeId, void *typeContext,
                    const UA_NodeId *nodeId, void **nodeContext) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "New missionData created");

    /* Find the NodeId of the status child variable */
    UA_RelativePathElement rpe;
    UA_RelativePathElement_init(&rpe);
    rpe.referenceTypeId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT);
    rpe.isInverse = false;
    rpe.includeSubtypes = false;
    rpe.targetName = UA_QUALIFIEDNAME(1, "AckPano");

    UA_BrowsePath bp;
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;

    UA_BrowsePathResult bpr =
        UA_Server_translateBrowsePathToNodeIds(server, &bp);
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;

    /* Set the AckPano value */
    UA_Boolean ackPano = 0;
    UA_Variant ackPanoValue;
    UA_Variant_setScalar(&ackPanoValue, &ackPano, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, ackPanoValue);
    UA_BrowsePathResult_clear(&bpr);

    /*find Indice Gare*/
    rpe.targetName = UA_QUALIFIEDNAME(1, "IndiceGare");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;
    
    /* Set the etat value */
    UA_Int32 indiceGare = 0;
    UA_Variant indiceGareValue;
    UA_Variant_setScalar(&indiceGareValue, &indiceGare, &UA_TYPES[UA_TYPES_INT32]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, indiceGareValue);
    UA_BrowsePathResult_clear(&bpr);
    
    /*find Requete */
    rpe.targetName = UA_QUALIFIEDNAME(1, "Requete");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;
        
    /* Set the requete value */
    UA_Boolean requete = 0;
    UA_Variant requeteValue;
    UA_Variant_setScalar(&requeteValue, &requete, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, requeteValue);
    UA_BrowsePathResult_clear(&bpr);
    
    
    /*find type*/
    rpe.targetName = UA_QUALIFIEDNAME(1, "Type");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;
        
    /* Set the type value */
    UA_Int32 type = 0;
    UA_Variant typeValue;
    UA_Variant_setScalar(&typeValue, &type, &UA_TYPES[UA_TYPES_INT32]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, typeValue);
    UA_BrowsePathResult_clear(&bpr);
    /* At this point we could replace the node context .. */

    return UA_STATUSCODE_GOOD;
}


static void
addGareTypeConstructor(UA_Server *server) {
    UA_NodeTypeLifecycle lifecycle;
    lifecycle.constructor = gareTypeConstructor;
    lifecycle.destructor = NULL;
    UA_Server_setNodeTypeLifecycle(server, gareTypeId, lifecycle);
}



static void
addMissionDataTypeConstructor(UA_Server *server) {
    UA_NodeTypeLifecycle lifecycle;
    lifecycle.constructor = missionDataTypeConstructor;
    lifecycle.destructor = NULL;
    UA_Server_setNodeTypeLifecycle(server, missionDataTypeId, lifecycle);
}
/*
static void
addZoneTypeConstructor(UA_Server *server) {
    UA_NodeTypeLifecycle lifecycle;
    lifecycle.constructor = zoneTypeConstructor;
    lifecycle.destructor = NULL;
    UA_Server_setNodeTypeLifecycle(server, zoneTypeId, lifecycle);
}
*/

/** It follows the main server code, making use of the above definitions. */

static volatile UA_Boolean running = true;
static void stopHandler(int sign) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    running = false;
}

int main(void) {
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    UA_Server *server = UA_Server_new();
    UA_ServerConfig_setDefault(UA_Server_getConfig(server));

    // batiment_40
    UA_NodeId batId =  manuallyDefineBat40(server);    
    // |- Zones    
    defineObjectTypesZones(server);
    UA_NodeId zonesId = addZonesObjectInstance(server, "Zones", batId);    
    //      |- Zone
    defineObjectTypesZone(server);
    UA_NodeId z1Id = addZoneObjectInstance(server, "Z1", zonesId);    

    //          |- Gares
    defineObjectTypesGares(server);
    UA_NodeId garesId = addGaresObjectInstance(server, "Gares", z1Id);    
    //              |- Gare        
    defineObjectTypesGare(server);    
    addGareTypeConstructor(server);
    addGareObjectInstance(server, "G1", garesId);
    addGareObjectInstance(server, "G2", garesId);
    addGareObjectInstance(server, "G3", garesId);
    addGareObjectInstance(server, "G4", garesId);
    //          |- Mission
    defineObjectTypesMission(server);
    UA_NodeId missionId = addMissionObjectInstance(server, "Mission", z1Id);
    //              |- MissionData        
    defineObjectTypesMissionData(server);
    addMissionDataTypeConstructor(server);
    addMissionDataObjectInstance(server, "MissionData", missionId);    
    
    
    UA_StatusCode retval = UA_Server_run(server, &running);

    UA_Server_delete(server);
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}
