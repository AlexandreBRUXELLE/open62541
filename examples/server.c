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
                            UA_QUALIFIEDNAME(0, "Batiment_40"), UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &batId);

    UA_VariableAttributes panoAlarmAttr = UA_VariableAttributes_default;
    UA_Boolean panoAlarmValue = true;
    UA_Variant_setScalar(&panoAlarmAttr.value, &panoAlarmValue, &UA_TYPES[UA_TYPES_BOOLEAN]);
    panoAlarmAttr.displayName = UA_LOCALIZEDTEXT("en-US", "PanoAlarmeIncendie");
    panoAlarmAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, batId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "PanoAlarmeIncendie"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), panoAlarmAttr, NULL, NULL);

    UA_VariableAttributes btnAlarmAttr = UA_VariableAttributes_default;
    UA_Boolean btnAlarmValue = true;
    UA_Variant_setScalar(&btnAlarmAttr.value, &btnAlarmValue, &UA_TYPES[UA_TYPES_BOOLEAN]);
    btnAlarmAttr.displayName = UA_LOCALIZEDTEXT("en-US", "BtnAlarmeIncendie");
    btnAlarmAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, batId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "BtnAlarmeIncendie"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), btnAlarmAttr, NULL, NULL);
    
    
    UA_VariableAttributes automatBit2VieAttr = UA_VariableAttributes_default;
    UA_Boolean automatBit2VieValue = true;
    UA_Variant_setScalar(&automatBit2VieAttr.value, &automatBit2VieValue, &UA_TYPES[UA_TYPES_BOOLEAN]);
    automatBit2VieAttr.displayName = UA_LOCALIZEDTEXT("en-US", "AutomateBit2Vie");
    automatBit2VieAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, batId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "AutomateBit2Vie"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), automatBit2VieAttr, NULL, NULL);

    UA_VariableAttributes etatInstallationAttr = UA_VariableAttributes_default;
    UA_Int32 etatInstallationValue = 0;
    UA_Variant_setScalar(&etatInstallationAttr.value, &etatInstallationValue, &UA_TYPES[UA_TYPES_INT32]);
    etatInstallationAttr.displayName = UA_LOCALIZEDTEXT("en-US", "EtatInstallation");
    etatInstallationAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, batId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "EtatInstallation"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), etatInstallationAttr, NULL, NULL);

    UA_VariableAttributes modeVidageAttr = UA_VariableAttributes_default;
    UA_Boolean modeVidageValue = false;
    UA_Variant_setScalar(&modeVidageAttr.value, &modeVidageValue, &UA_TYPES[UA_TYPES_BOOLEAN]);
    modeVidageAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ModeVidage");
    modeVidageAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, batId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "ModeVidage"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), modeVidageAttr, NULL, NULL);
    
    UA_VariableAttributes panorameBit2VieAttr = UA_VariableAttributes_default;
    UA_Boolean panorameBit2VieValue = true;
    UA_Variant_setScalar(&panorameBit2VieAttr.value, &panorameBit2VieValue, &UA_TYPES[UA_TYPES_BOOLEAN]);
    panorameBit2VieAttr.displayName = UA_LOCALIZEDTEXT("en-US", "PanoramaBit2Vie");
    panorameBit2VieAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, batId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "PanoramaBit2Vie"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), panorameBit2VieAttr, NULL, NULL);
    
    return batId;
}

static UA_NodeId
manuallyDefineCata(UA_Server *server) {
    UA_NodeId cataId; /* get the nodeid assigned by the server */
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Cataphorese");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(0, "Cataphorese"), UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &cataId);
    return cataId;
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
UA_NodeId dbEchAmrTypeId = {1, UA_NODEIDTYPE_NUMERIC, {1007}};
UA_NodeId posteTypeId = {1, UA_NODEIDTYPE_NUMERIC, {1008}};
UA_NodeId gareTypeId = {1, UA_NODEIDTYPE_NUMERIC, {1005}};
UA_NodeId missionDataTypeId = {1, UA_NODEIDTYPE_NUMERIC, {1006}};
UA_NodeId garesTypeId = {1, UA_NODEIDTYPE_NUMERIC, {1003}};
UA_NodeId missionTypeId = {1, UA_NODEIDTYPE_NUMERIC, {1004}};
UA_NodeId zonesTypeId = {1, UA_NODEIDTYPE_NUMERIC, {1001}};
UA_NodeId zoneTypeId = {1, UA_NODEIDTYPE_NUMERIC, {1002}};

static void
defineObjectTypesPoste(UA_Server *server) {
    /* Define the object type for "Gare" */
    UA_NodeId posteId; /* get the nodeid assigned by the server */
    UA_ObjectTypeAttributes posteTypeAttr = UA_ObjectTypeAttributes_default;
    posteTypeAttr.displayName = UA_LOCALIZEDTEXT("en-US", "PosteType");
    UA_Server_addObjectTypeNode(server, UA_NODEID_NULL,
                                UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                                UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(0, "PosteType"), posteTypeAttr,
                                NULL, &posteId);

    UA_VariableAttributes typePieceAttr = UA_VariableAttributes_default;
    typePieceAttr.displayName = UA_LOCALIZEDTEXT("en-US", "TypePiece");
    typePieceAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    typePieceAttr.dataType = UA_TYPES[UA_TYPES_INT16].typeId ;
    UA_NodeId typePieceId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, posteId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "TypePiece"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), typePieceAttr, NULL, &typePieceId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, typePieceId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);


    UA_VariableAttributes enGareAttr = UA_VariableAttributes_default;
    enGareAttr.displayName = UA_LOCALIZEDTEXT("en-US", "EnGare");
    enGareAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    enGareAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId enGareId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, posteId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "EnGare"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), enGareAttr, NULL, &enGareId);
    /* Make the etat mandatory */
    UA_Server_addReference(server, enGareId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
   

    UA_VariableAttributes horsZoneAttr = UA_VariableAttributes_default;
    horsZoneAttr.displayName = UA_LOCALIZEDTEXT("en-US", "HorsZone");
    horsZoneAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    horsZoneAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId horsZoneId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, posteId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "HorsZone"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), horsZoneAttr, NULL, &horsZoneId);
    /* Make the etat mandatory */
   UA_Server_addReference(server, horsZoneId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
  
    UA_VariableAttributes autoInAttr = UA_VariableAttributes_default;
    autoInAttr.displayName = UA_LOCALIZEDTEXT("en-US", "AutoIn");
    autoInAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    autoInAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId autoInId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, posteId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "AutoIn"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), autoInAttr, NULL, &autoInId);
    /* Make the etat mandatory */
   UA_Server_addReference(server, autoInId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
   
    UA_VariableAttributes autoOutAttr = UA_VariableAttributes_default;
    autoOutAttr.displayName = UA_LOCALIZEDTEXT("en-US", "AutoOut");
    autoOutAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    autoOutAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId autoOutId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, posteId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "AutoOut"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), autoOutAttr, NULL, &autoOutId);
    /* Make the etat mandatory */
   UA_Server_addReference(server, autoOutId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
   
   
   /* Define the object type for "Gare" */
    UA_ObjectTypeAttributes ptAttr = UA_ObjectTypeAttributes_default;
    ptAttr.displayName = UA_LOCALIZEDTEXT("en-US", "PosteType");
    UA_Server_addObjectTypeNode(server, posteTypeId,
                                posteId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(0, "PosteType"), ptAttr,
                                NULL, NULL);

    
}

static void
defineObjectTypesGare(UA_Server *server) {
    /* Define the object type for "Gare" */
    UA_NodeId gareId; /* get the nodeid assigned by the server */
    UA_ObjectTypeAttributes gareTypeAttr = UA_ObjectTypeAttributes_default;
    gareTypeAttr.displayName = UA_LOCALIZEDTEXT("en-US", "GareType");
    UA_Server_addObjectTypeNode(server, UA_NODEID_NULL,
                                UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                                UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(0, "GareType"), gareTypeAttr,
                                NULL, &gareId);

    UA_VariableAttributes contenuAttr = UA_VariableAttributes_default;
    contenuAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Contenu");
    contenuAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    contenuAttr.dataType = UA_TYPES[UA_TYPES_INT32].typeId ;
    UA_NodeId contenuId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, gareId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "Contenu"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), contenuAttr, NULL, &contenuId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, contenuId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);


    UA_VariableAttributes etatAttr = UA_VariableAttributes_default;
    etatAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Etat");
    etatAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    etatAttr.dataType = UA_TYPES[UA_TYPES_INT32].typeId ;
    UA_NodeId etatId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, gareId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "Etat"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), etatAttr, NULL, &etatId);
    /* Make the etat mandatory */
    UA_Server_addReference(server, etatId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
   

    UA_VariableAttributes messageAttr = UA_VariableAttributes_default;
    messageAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Message");
    messageAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    messageAttr.dataType = UA_TYPES[UA_TYPES_STRING].typeId ;
    UA_NodeId messageId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, gareId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "Message"),
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
                                UA_QUALIFIEDNAME(0, "GareType"), gtAttr,
                                NULL, NULL);

    
}

static void
defineObjectTypesDbEchAmr(UA_Server *server) {
    /* Define the object type for "DbEchAmr" */
    UA_NodeId dbEchAmrId; /* get the nodeid assigned by the server */
    UA_ObjectTypeAttributes dbEchAmrAttr = UA_ObjectTypeAttributes_default;
    dbEchAmrAttr.displayName = UA_LOCALIZEDTEXT("en-US", "DbEchAmrType");
    UA_Server_addObjectTypeNode(server, UA_NODEID_NULL,
                                UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                                UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(0, "DbEchAmrType"), dbEchAmrAttr,
                                NULL, &dbEchAmrId);
    
    UA_VariableAttributes incycliqueAttr = UA_VariableAttributes_default;
    incycliqueAttr.displayName = UA_LOCALIZEDTEXT("en-US", "InCyclique");
    incycliqueAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    incycliqueAttr.dataType = UA_TYPES[UA_TYPES_INT16].typeId ;
    UA_NodeId incycliqueId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, dbEchAmrId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "InCyclique"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), incycliqueAttr, NULL, &incycliqueId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, incycliqueId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);

    UA_VariableAttributes inAlarmAttr = UA_VariableAttributes_default;
    inAlarmAttr.displayName = UA_LOCALIZEDTEXT("en-US", "InAlarm");
    inAlarmAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    inAlarmAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId inAlarmId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, dbEchAmrId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "InAlarm"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), inAlarmAttr, NULL, &inAlarmId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, inAlarmId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
    
    UA_VariableAttributes OutAlarmAttr = UA_VariableAttributes_default;
    OutAlarmAttr.displayName = UA_LOCALIZEDTEXT("en-US", "OutAlarm");
    OutAlarmAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    OutAlarmAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId OutAlarmId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, dbEchAmrId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "OutAlarm"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), OutAlarmAttr, NULL, &OutAlarmId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, OutAlarmId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
    
    UA_VariableAttributes inAmrEsAttr = UA_VariableAttributes_default;
    inAmrEsAttr.displayName = UA_LOCALIZEDTEXT("en-US", "InAmrEs");
    inAmrEsAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    inAmrEsAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId inAmrEsId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, dbEchAmrId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "InAmrEs"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), inAmrEsAttr, NULL, &inAmrEsId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, inAmrEsId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
    
    UA_VariableAttributes outCharAutoAttr = UA_VariableAttributes_default;
    outCharAutoAttr.displayName = UA_LOCALIZEDTEXT("en-US", "OutCharAuto");
    outCharAutoAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    outCharAutoAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId outCharAutoId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, dbEchAmrId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "OutCharAuto"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), outCharAutoAttr, NULL, &outCharAutoId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, outCharAutoId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
    
    UA_VariableAttributes inFaultAttr = UA_VariableAttributes_default;
    inFaultAttr.displayName = UA_LOCALIZEDTEXT("en-US", "InFault");
    inFaultAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    inFaultAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId inFaultId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, dbEchAmrId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "InFault"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), inFaultAttr, NULL, &inFaultId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, inFaultId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
    
    UA_VariableAttributes OutFaultAttr = UA_VariableAttributes_default;
    OutFaultAttr.displayName = UA_LOCALIZEDTEXT("en-US", "OutFault");
    OutFaultAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    OutFaultAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId OutFaultId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, dbEchAmrId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "OutFault"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), OutFaultAttr, NULL, &OutFaultId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, OutFaultId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
    
    
    UA_VariableAttributes outcycliqueAttr = UA_VariableAttributes_default;
    outcycliqueAttr.displayName = UA_LOCALIZEDTEXT("en-US", "OutCyclique");
    outcycliqueAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    outcycliqueAttr.dataType = UA_TYPES[UA_TYPES_INT16].typeId ;
    UA_NodeId outcycliqueId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, dbEchAmrId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "OutCyclique"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), outcycliqueAttr, NULL, &outcycliqueId);
    // Make the contenu mandatory 
    UA_Server_addReference(server, outcycliqueId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);

    
    UA_VariableAttributes invidageAttr = UA_VariableAttributes_default;
    invidageAttr.displayName = UA_LOCALIZEDTEXT("en-US", "InVidage");
    invidageAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    invidageAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId invidageId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, dbEchAmrId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "InVidage"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), invidageAttr, NULL, &invidageId);
    /* Make the vidage mandatory */
    UA_Server_addReference(server, invidageId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
    
    UA_VariableAttributes outvidageAttr = UA_VariableAttributes_default;
    invidageAttr.displayName = UA_LOCALIZEDTEXT("en-US", "OutVidage");
    invidageAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    invidageAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId outvidageId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, dbEchAmrId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "OutVidage"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), outvidageAttr, NULL, &outvidageId);
    /* Make the vidage mandatory */
    UA_Server_addReference(server, outvidageId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
    
    UA_VariableAttributes inPdChargAttr = UA_VariableAttributes_default;
    inPdChargAttr.displayName = UA_LOCALIZEDTEXT("en-US", "InPdCharg");
    inPdChargAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    inPdChargAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId inPdChargId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, dbEchAmrId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "InPdCharg"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), inPdChargAttr, NULL, &inPdChargId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, inPdChargId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
    
    UA_VariableAttributes inPdDechaAttr = UA_VariableAttributes_default;
    inPdDechaAttr.displayName = UA_LOCALIZEDTEXT("en-US", "InPdDecha");
    inPdDechaAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    inPdDechaAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId inPdDechaId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, dbEchAmrId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "InPdDecha"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), inPdDechaAttr, NULL, &inPdDechaId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, inPdDechaId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
    
    UA_VariableAttributes inPgDechaAttr = UA_VariableAttributes_default;
    inPgDechaAttr.displayName = UA_LOCALIZEDTEXT("en-US", "InPgDecha");
    inPgDechaAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    inPgDechaAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId inPgDechargId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, dbEchAmrId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "InPgDecha"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), inPgDechaAttr, NULL, &inPgDechargId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, inPgDechargId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
    
    
    UA_VariableAttributes inPgChargAttr = UA_VariableAttributes_default;
    inPgChargAttr.displayName = UA_LOCALIZEDTEXT("en-US", "InPgCharg");
    inPgChargAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    inPgChargAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId inPgChargId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, dbEchAmrId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "InPgCharg"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), inPgChargAttr, NULL, &inPgChargId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, inPgChargId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);


    UA_VariableAttributes inPgEnGareAttr = UA_VariableAttributes_default;
    inPgEnGareAttr.displayName = UA_LOCALIZEDTEXT("en-US", "InPgEnGare");
    inPgEnGareAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    inPgEnGareAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId inPgEnGareId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, dbEchAmrId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "InPgEnGare"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), inPgEnGareAttr, NULL, &inPgEnGareId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, inPgEnGareId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
    


    UA_VariableAttributes inPgHorsZoneAttr = UA_VariableAttributes_default;
    inPgHorsZoneAttr.displayName = UA_LOCALIZEDTEXT("en-US", "InPgHorsZone");
    inPgHorsZoneAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    inPgHorsZoneAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId inPgHorsZoneId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, dbEchAmrId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "InPgHorsZone"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), inPgHorsZoneAttr, NULL, &inPgHorsZoneId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, inPgHorsZoneId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
    
    UA_VariableAttributes inPdEnGareAttr = UA_VariableAttributes_default;
    inPdEnGareAttr.displayName = UA_LOCALIZEDTEXT("en-US", "InPdEnGare");
    inPdEnGareAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    inPdEnGareAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId inPdEnGareId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, dbEchAmrId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "InPdEnGare"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), inPdEnGareAttr, NULL, &inPdEnGareId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, inPdEnGareId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
    
    UA_VariableAttributes inPdHorsZoneAttr = UA_VariableAttributes_default;
    inPdHorsZoneAttr.displayName = UA_LOCALIZEDTEXT("en-US", "InPdHorsZone");
    inPdHorsZoneAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    inPdHorsZoneAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId inPdHorsZoneId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, dbEchAmrId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "InPdHorsZone"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), inPdHorsZoneAttr, NULL, &inPdHorsZoneId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, inPdHorsZoneId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
    
    UA_VariableAttributes inPdTypePieceAttr = UA_VariableAttributes_default;
    inPdTypePieceAttr.displayName = UA_LOCALIZEDTEXT("en-US", "InPdTypePiece");
    inPdTypePieceAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    inPdTypePieceAttr.dataType = UA_TYPES[UA_TYPES_INT16].typeId ;
    UA_NodeId inPdTypePieceId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, dbEchAmrId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "InPdTypePiece"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), inPdTypePieceAttr, NULL, &inPdTypePieceId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, inPdTypePieceId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
    
    UA_VariableAttributes inPgTypePieceAttr = UA_VariableAttributes_default;
    inPgTypePieceAttr.displayName = UA_LOCALIZEDTEXT("en-US", "InPgTypePiece");
    inPgTypePieceAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    inPgTypePieceAttr.dataType = UA_TYPES[UA_TYPES_INT16].typeId ;
    UA_NodeId inPgTypePieceId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, dbEchAmrId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "InPgTypePiece"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), inPgTypePieceAttr, NULL, &inPgTypePieceId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, inPgTypePieceId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
    
    // Define the object type for "DbEchAmr" 
    UA_ObjectTypeAttributes dbtAttr = UA_ObjectTypeAttributes_default;
    dbtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "DbEchAmrType");
    UA_Server_addObjectTypeNode(server, dbEchAmrTypeId,
                                dbEchAmrId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(0, "DbEchAmrType"), dbtAttr,
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
                                UA_QUALIFIEDNAME(0, "GaresType"), garesTypeAttr,
                                NULL, &garesId);
    
       // Define the object type for "Gare" 
    UA_ObjectTypeAttributes gtAttr = UA_ObjectTypeAttributes_default;
    gtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "GaresType");
    UA_Server_addObjectTypeNode(server, garesTypeId,
                                garesId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(0, "GaresType"), gtAttr,
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
                                UA_QUALIFIEDNAME(0, "MissionData"), missionDataTypeAttr,
                                NULL, &missionDataId);

    UA_VariableAttributes ackPanoAttr = UA_VariableAttributes_default;
    ackPanoAttr.displayName = UA_LOCALIZEDTEXT("en-US", "AckPano");
    ackPanoAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    ackPanoAttr.dataType = UA_TYPES[UA_TYPES_INT32].typeId ;
    UA_NodeId ackPanoId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, missionDataId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "AckPano"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), ackPanoAttr, NULL, &ackPanoId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, ackPanoId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);


    UA_VariableAttributes indiceGareAttr = UA_VariableAttributes_default;
    indiceGareAttr.displayName = UA_LOCALIZEDTEXT("en-US", "IndiceGare");
    indiceGareAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    indiceGareAttr.dataType = UA_TYPES[UA_TYPES_INT32].typeId ;
    UA_NodeId indiceGareId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, missionDataId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "IndiceGare"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), indiceGareAttr, NULL, &indiceGareId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, indiceGareId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
   

    UA_VariableAttributes requeteAttr = UA_VariableAttributes_default;
    requeteAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Requete");
    requeteAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    requeteAttr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId ;
    UA_NodeId requeteId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, missionDataId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "Requete"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), requeteAttr, NULL, &requeteId);
    /* Make the contenu mandatory */
    UA_Server_addReference(server, requeteId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
    
    UA_VariableAttributes typeAttr = UA_VariableAttributes_default;
    typeAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Type");
    typeAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    typeAttr.dataType = UA_TYPES[UA_TYPES_INT32].typeId ;
    UA_NodeId typeId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, missionDataId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(0, "Type"),
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
                                UA_QUALIFIEDNAME(0, "MissionDataType"), mdtAttr,
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
                                UA_QUALIFIEDNAME(0, "MissionType"), missionTypeAttr,
                                NULL, &missionId);

    
       // Define the object type for "Gare" 
    UA_ObjectTypeAttributes gtAttr = UA_ObjectTypeAttributes_default;
    gtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "MissionType");
    UA_Server_addObjectTypeNode(server, missionTypeId,
                                missionId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(0, "MissionType"), gtAttr,
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
                                UA_QUALIFIEDNAME(0, "ZonesType"), zonesTypeAttr,
                                NULL, &zonesId);

    
    // Define the object type for "Zones" 
    UA_ObjectTypeAttributes zstAttr = UA_ObjectTypeAttributes_default;
    zstAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ZonesType");
    UA_Server_addObjectTypeNode(server, zonesTypeId,
                                zonesId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(0, "ZonesType"), zstAttr,
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
                                UA_QUALIFIEDNAME(0, "ZoneType"), zoneTypeAttr,
                                NULL, &zoneId);

    
    // Define the object type for "Zone" 
    UA_ObjectTypeAttributes ztAttr = UA_ObjectTypeAttributes_default;
    ztAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ZoneType");
    UA_Server_addObjectTypeNode(server, zoneTypeId,
                                zoneId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(0, "ZoneType"), ztAttr,
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
addPosteObjectInstance(UA_Server *server, char *name, UA_NodeId idToInsert) {
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", name);
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            idToInsert,//UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(0, name),
                            posteTypeId, /* this refers to the object type
                                           identifier */
                            oAttr, NULL, NULL);
}


static void
addGareObjectInstance(UA_Server *server, char *name, UA_NodeId idToInsert) {
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", name);
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            idToInsert,//UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(0, name),
                            gareTypeId, /* this refers to the object type
                                           identifier */
                            oAttr, NULL, NULL);
}

static UA_NodeId
addDbEchAmrObjectInstance(UA_Server *server, char *name, UA_NodeId idToInsert) {
    UA_NodeId refDbEchAmrTypeId;
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", name);
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            idToInsert,//UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(0, name),
                            dbEchAmrTypeId, /* this refers to the object type
                                           identifier */
                            oAttr, NULL, &refDbEchAmrTypeId);
    return refDbEchAmrTypeId;
}


static UA_NodeId
addGaresObjectInstance(UA_Server *server, char *name, UA_NodeId idToInsert) {
    UA_NodeId refGaresTypeId;
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", name);
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            idToInsert,//UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(0, name),
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
                            UA_QUALIFIEDNAME(0, name),
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
                            UA_QUALIFIEDNAME(0, name),
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
                            UA_QUALIFIEDNAME(0, name),
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
                            UA_QUALIFIEDNAME(0, name),
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
posteTypeConstructor(UA_Server *server,
                    const UA_NodeId *sessionId, void *sessionContext,
                    const UA_NodeId *typeId, void *typeContext,
                    const UA_NodeId *nodeId, void **nodeContext) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "New poste created");

    /* Find the NodeId of the status child variable */
    UA_RelativePathElement rpe;
    UA_RelativePathElement_init(&rpe);
    rpe.referenceTypeId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT);
    rpe.isInverse = false;
    rpe.includeSubtypes = false;
    rpe.targetName = UA_QUALIFIEDNAME(0, "TypePiece");

    UA_BrowsePath bp;
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;

    UA_BrowsePathResult bpr =
        UA_Server_translateBrowsePathToNodeIds(server, &bp);
        bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;

    /* Set the typePiece value */
    UA_Int16 typePiece = 0;
    UA_Variant typePieceValue;
    UA_Variant_setScalar(&typePieceValue, &typePiece, &UA_TYPES[UA_TYPES_INT16]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, typePieceValue);
    UA_BrowsePathResult_clear(&bpr);

    /*find enGare*/
    rpe.targetName = UA_QUALIFIEDNAME(0, "EnGare");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;
    
    /* Set the enGare value */
    UA_Boolean enGare = false;
    UA_Variant enGareValue;
    UA_Variant_setScalar(&enGareValue, &enGare, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, enGareValue);
    UA_BrowsePathResult_clear(&bpr);
      
    
    /*find horsZone*/
    rpe.targetName = UA_QUALIFIEDNAME(0, "HorsZone");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;
        
    /* Set the horsZone value */
    UA_Boolean horsZone = false;
    UA_Variant horsZoneValue;
    UA_Variant_setScalar(&horsZoneValue, &horsZone, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, horsZoneValue);
    UA_BrowsePathResult_clear(&bpr);
    
    /*find AutoIn*/
    rpe.targetName = UA_QUALIFIEDNAME(0, "AutoIn");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;
        
    /* Set the autoIn value */
    UA_Boolean autoIn = false;
    UA_Variant autoInValue;
    UA_Variant_setScalar(&autoInValue, &autoIn, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, horsZoneValue);
    UA_BrowsePathResult_clear(&bpr);
    
    /*find AutoOut*/
    rpe.targetName = UA_QUALIFIEDNAME(0, "AutoOut");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;
        
    /* Set the autoOut value */
    UA_Boolean autoOut = false;
    UA_Variant autoOutValue;
    UA_Variant_setScalar(&autoOutValue, &autoOut, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, autoOutValue);
    UA_BrowsePathResult_clear(&bpr);
    /* At this point we could replace the node context .. */

    return UA_STATUSCODE_GOOD;
}

static UA_StatusCode
dbechAmrTypeConstructor(UA_Server *server,
                    const UA_NodeId *sessionId, void *sessionContext,
                    const UA_NodeId *typeId, void *typeContext,
                    const UA_NodeId *nodeId, void **nodeContext) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "New dbechAmr created");

    /* Find the NodeId of the status child variable */
    UA_RelativePathElement rpe;
    UA_RelativePathElement_init(&rpe);
    rpe.referenceTypeId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT);
    rpe.isInverse = false;
    rpe.includeSubtypes = false;
    rpe.targetName = UA_QUALIFIEDNAME(0, "InCyclique");

    UA_BrowsePath bp;
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;

    UA_BrowsePathResult bpr =
        UA_Server_translateBrowsePathToNodeIds(server, &bp);
        bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;

    /* Set the status value */
    UA_Int16 incyclique = 0;
    UA_Variant incycliqueValue;
    UA_Variant_setScalar(&incycliqueValue, &incyclique, &UA_TYPES[UA_TYPES_INT16]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, incycliqueValue);
    UA_BrowsePathResult_clear(&bpr);

    //find OutCyclique
    rpe.targetName = UA_QUALIFIEDNAME(0, "OutCyclique");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;
        
    UA_Int16 outcyclique = 0;
    UA_Variant outcycliqueValue;
    UA_Variant_setScalar(&outcycliqueValue, &outcyclique, &UA_TYPES[UA_TYPES_INT16]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, outcycliqueValue);
    UA_BrowsePathResult_clear(&bpr);
    
    
    /*find InVidage*/
    rpe.targetName = UA_QUALIFIEDNAME(0, "InVidage");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;
    
    /* Set the Vidage value */
    UA_Boolean invidage = 0;
    UA_Variant invidageValue;
    UA_Variant_setScalar(&invidageValue, &invidage, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, invidageValue);
    UA_BrowsePathResult_clear(&bpr);

    
    /*find OutVidage*/
    rpe.targetName = UA_QUALIFIEDNAME(0, "OutVidage");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;
    
    /* Set the Vidage value */
    UA_Boolean outvidage = 0;
    UA_Variant outvidageValue;
    UA_Variant_setScalar(&outvidageValue, &outvidage, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, outvidageValue);
    UA_BrowsePathResult_clear(&bpr);
    
    /*find InAlarm*/
    rpe.targetName = UA_QUALIFIEDNAME(0, "InAlarm");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;
    
    /* Set the Vidage value */
    UA_Boolean inAlamr = 0;
    UA_Variant  inAlamrValue;
    UA_Variant_setScalar(&inAlamrValue, &inAlamr, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, inAlamrValue);
    UA_BrowsePathResult_clear(&bpr);
    
    /*find InAmrEs*/
    rpe.targetName = UA_QUALIFIEDNAME(0, "InAmrEs");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;
    
    /* Set the Vidage value */
    UA_Boolean inAmrEs = 0;
    UA_Variant inAmrEsValue;
    UA_Variant_setScalar(&inAmrEsValue, &inAmrEs, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, inAmrEsValue);
    UA_BrowsePathResult_clear(&bpr);

    /*find InFault*/
    rpe.targetName = UA_QUALIFIEDNAME(0, "InFault");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;
    
    /* Set the Vidage value */
    UA_Boolean inFault = 0;
    UA_Variant inFaultValue;
    UA_Variant_setScalar(&inFaultValue, &inFault, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, inFaultValue);
    UA_BrowsePathResult_clear(&bpr);
    
    return UA_STATUSCODE_GOOD;
}

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
    rpe.targetName = UA_QUALIFIEDNAME(0, "Contenu");

    UA_BrowsePath bp;
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;

    UA_BrowsePathResult bpr =
        UA_Server_translateBrowsePathToNodeIds(server, &bp);
        bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
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
    rpe.targetName = UA_QUALIFIEDNAME(0, "Etat");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;
    
    /* Set the etat value */
    UA_Int32 etat = 0;
    UA_Variant etatValue;
    UA_Variant_setScalar(&etatValue, &etat, &UA_TYPES[UA_TYPES_INT32]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, etatValue);
    UA_BrowsePathResult_clear(&bpr);
      
    
    /*find message*/
    rpe.targetName = UA_QUALIFIEDNAME(0, "Message");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
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
    rpe.targetName = UA_QUALIFIEDNAME(0, "AckPano");

    UA_BrowsePath bp;
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "%i", bp.startingNode.identifier.numeric);
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;

    UA_BrowsePathResult bpr =
        UA_Server_translateBrowsePathToNodeIds(server, &bp);
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;

    /* Set the AckPano value */
    UA_Int32 ackPano = 0;
    UA_Variant ackPanoValue;
    UA_Variant_setScalar(&ackPanoValue, &ackPano, &UA_TYPES[UA_TYPES_INT32]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, ackPanoValue);
    UA_BrowsePathResult_clear(&bpr);

    /*find Indice Gare*/
    rpe.targetName = UA_QUALIFIEDNAME(0, "IndiceGare");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
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
    rpe.targetName = UA_QUALIFIEDNAME(0, "Requete");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;
        
    /* Set the requete value */
    UA_Boolean requete = false;
    UA_Variant requeteValue;
    UA_Variant_setScalar(&requeteValue, &requete, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, requeteValue);
    UA_BrowsePathResult_clear(&bpr);
    
    
    /*find type*/
    rpe.targetName = UA_QUALIFIEDNAME(0, "Type");
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;
    bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
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

static void
addPosteTypeConstructor(UA_Server *server) {
    UA_NodeTypeLifecycle lifecycle;
    lifecycle.constructor = posteTypeConstructor;
    lifecycle.destructor = NULL;
    UA_Server_setNodeTypeLifecycle(server, posteTypeId, lifecycle);
}

static void
addDbEchAmrTypeConstructor(UA_Server *server) {
    UA_NodeTypeLifecycle lifecycle;
    lifecycle.constructor = dbechAmrTypeConstructor;
    lifecycle.destructor = NULL;
    UA_Server_setNodeTypeLifecycle(server, dbEchAmrTypeId, lifecycle);
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

static void 
garesFactory(UA_Server* server, int nbGares, UA_NodeId parentNodeId){
    
    for(int ii = 1 ; ii<=nbGares ; ii++){
         char gareName[5] = "";
         snprintf(gareName, sizeof(gareName), "G%i", ii);
         addGareObjectInstance(server, gareName, parentNodeId);
    }
    
}

static void 
zoneFactory(UA_Server* server, char* zoneName, int nbGares, UA_NodeId parentNodeId){
    
    UA_NodeId z1Id = addZoneObjectInstance(server, zoneName, parentNodeId);    
    //          |- Gares
    UA_NodeId garesId = addGaresObjectInstance(server, "Gares", z1Id);    
    //              |- Gare        
    addGareTypeConstructor(server);
    garesFactory(server,nbGares, garesId);
    //          |- Mission
    UA_NodeId missionId = addMissionObjectInstance(server, "Mission", z1Id);
    //              |- MissionData        
    addMissionDataTypeConstructor(server);
    addMissionDataObjectInstance(server, "MissionData", missionId);  
    
}


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
    //cataphorese
    UA_NodeId cataId = manuallyDefineCata(server);
    defineObjectTypesDbEchAmr(server);
    addDbEchAmrTypeConstructor(server);
    defineObjectTypesPoste(server);
    addPosteTypeConstructor(server);   
    UA_NodeId dbEchAmrId = addDbEchAmrObjectInstance(server, "DbEchAmr", cataId);       
    addPosteObjectInstance(server, "PosteG", dbEchAmrId);    
    addPosteObjectInstance(server, "PosteD", dbEchAmrId); 
    
    //// |- Zones    
    defineObjectTypesZones(server);
    UA_NodeId zonesId = addZonesObjectInstance(server, "SousZones", batId);    
    //      |- Zone
    defineObjectTypesZone(server);
    //          |- Gares
    defineObjectTypesGares(server);  
    //              |- Gare        
    defineObjectTypesGare(server);    
    //          |- Mission
    defineObjectTypesMission(server);
    //              |- MissionData        
    defineObjectTypesMissionData(server);

zoneFactory(server, "SZ1",   2, zonesId);
zoneFactory(server, "SZ2",   2, zonesId);
zoneFactory(server, "SZ3",   2, zonesId);
zoneFactory(server, "SZ4",   2, zonesId);
zoneFactory(server, "SZ5",   2, zonesId);

zoneFactory(server, "SZ6",   4, zonesId);    
zoneFactory(server, "SZ7",   4, zonesId);

zoneFactory(server, "SZ8",    4, zonesId);
zoneFactory(server, "SZ9",    4, zonesId);
zoneFactory(server, "SZ10",   4, zonesId);
zoneFactory(server, "SZ11",   4, zonesId);

zoneFactory(server, "SZ12",   2, zonesId);
zoneFactory(server, "SZ13",   2, zonesId);

zoneFactory(server, "SZ14",   2, zonesId);
zoneFactory(server, "SZ15",   2, zonesId);
zoneFactory(server, "SZ16",   2, zonesId);
zoneFactory(server, "SZ17",   2, zonesId);
zoneFactory(server, "SZ18",   2, zonesId);
zoneFactory(server, "SZ19",   2, zonesId);
zoneFactory(server, "SZ20",   2, zonesId);

zoneFactory(server, "SZ21",   6, zonesId);
zoneFactory(server, "SZ22",   4,zonesId);

zoneFactory(server, "SZ23",   4,zonesId);
zoneFactory(server, "SZ24",   7,zonesId);
zoneFactory(server, "SZ25",   7,zonesId);
zoneFactory(server, "SZ26",   6,zonesId);
zoneFactory(server, "SZ27",   2,zonesId);
zoneFactory(server, "SZ28",   7,zonesId);
zoneFactory(server, "SZ29",   7,zonesId);
zoneFactory(server, "SZ30",   6,zonesId);

zoneFactory(server, "SZ31",   4,zonesId);
zoneFactory(server, "SZ32",   4,zonesId);
zoneFactory(server, "SZ33",   4, zonesId);
zoneFactory(server, "SZ34",   4, zonesId);

zoneFactory(server, "SZ35",   6, zonesId);
zoneFactory(server, "SZ36",   2, zonesId);
zoneFactory(server, "SZ37",   1, zonesId);
zoneFactory(server, "SZ38",   2, zonesId);
zoneFactory(server, "SZ39",   1,zonesId);
zoneFactory(server, "SZ40",   2,zonesId);

zoneFactory(server, "SZ41",   4,zonesId);
zoneFactory(server, "SZ42",   12,zonesId);
zoneFactory(server, "SZ43",   16,zonesId);
zoneFactory(server, "SZ44",   66,zonesId);
zoneFactory(server, "SZ45",   2,zonesId);

    
    UA_StatusCode retval = UA_Server_run(server, &running);

    UA_Server_delete(server);
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}

