#!/bin/bash

file="$1"
output="$2"

{
cat <<EOF
digraph doxygraph
{
splines=true;
overlap=false;
    bgcolor="#ffe5e7";
subgraph cluster_0 {
    rankdir = TB;
    style=filled;
    color="#e1e6e8";
    fontsize=80.0
    labeljust="l"
    label="Controller"
    "classRG_1_1Controller_1_1GameController"
    "classRG_1_1Controller_1_1StateHandler"
    "classRG_1_1Controller_1_1GameStateHandler"
    "classRG_1_1Controller_1_1MenuStateHandler"
    {rank = same; "classRG_1_1Controller_1_1GameController"}
    {rank = same; "classRG_1_1Controller_1_1StateHandler"}
    {rank = same; "classRG_1_1Controller_1_1GameStateHandler","classRG_1_1Controller_1_1MenuStateHandler"}
}

subgraph cluster_1 {
    rankdir = TB;
    style=filled;
    color="#efdef5";
    fontsize=80.0
    labeljust="l"
    label="View"
    "classRG_1_1View_1_1View"
    "classRG_1_1View_1_1SoundManager"
    "classRG_1_1View_1_1Scene"
    "classRG_1_1View_1_1Room"
    "classRG_1_1View_1_1RoomHistory"
    "classRG_1_1View_1_1Room"
    "classRG_1_1View_1_1Player"
    "classRG_1_1View_1_1MenuScene"
    "classRG_1_1View_1_1IOManager"
    "classRG_1_1View_1_1GameScene"
    "classRG_1_1View_1_1Console"
    "classRG_1_1View_1_1Animation"
    {rank = same; "classRG_1_1View_1_1View"}
    {rank = same; "classRG_1_1View_1_1Scene"}
    {rank = same; "classRG_1_1View_1_1MenuScene", "classRG_1_1View_1_1GameScene"}
    {rank = same; "classRG_1_1View_1_1SoundManager", "classRG_1_1View_1_1IOManager", "classRG_1_1View_1_1Console"}
    {rank = same; "classRG_1_1View_1_1Room", "classRG_1_1View_1_1Player"}
    {rank = same; "classRG_1_1View_1_1Animation", "classRG_1_1View_1_1RoomHistory"}
}
subgraph cluster_3 {
    style=filled;
    color="#e59eaf";
    fontsize=80.0
    labeljust="l"
    label="Model"
    subgraph cluster_4 {
        rankdir = TB;
        labeljust="l"
        fontsize=50.0
        label="World Model"
        "classRG_1_1Model_1_1Model"
        "classRG_1_1Model_1_1Floor"
        "classRG_1_1Model_1_1Entity"
        "classRG_1_1Model_1_1Room"
        "classRG_1_1Model_1_1Object"
        "classRG_1_1Model_1_1DynamicObject"
        {rank = same; "classRG_1_1Model_1_1Model"}
        {rank = same; "classRG_1_1Model_1_1Floor","classRG_1_1Model_1_1Entity"}
        {rank = same; "classRG_1_1Model_1_1Room","classRG_1_1Model_1_1DynamicObject"}
        {rank = same; "classRG_1_1Model_1_1Object"}
    }

    subgraph cluster_5 {
        rankdir = TB;
        fontsize=50.0
        labeljust="l"
        label="Trading Model"
        "classRG_1_1NPC_1_1Request"
        "classRG_1_1NPC_1_1NPCWorldCycle"
        "classRG_1_1NPC_1_1MatchingEngine"
        "classRG_1_1NPC_1_1Market"
        "classRG_1_1NPC_1_1Item"
        "classRG_1_1NPC_1_1Intelligence"
        "classRG_1_1NPC_1_1HalfRequest"
        "classRG_1_1NPC_1_1Entity"
        "classRG_1_1NPC_1_1BasicIntelligence"
    }
}
EOF
} > "$output"

sed -e '1,3d' -e '$d' "$file" | sort >> "$output"

echo "}" >> "$output"

sed -i \
-e '/^"classb2Draw.*/d' \
-e '/^"classRG_1_1CacheManager.*/d' \
-e '/^"classRG_1_1DebugDraw.*/d' \
-e '/^"classRG_1_1StorageException.*/d' \
-e '/^"classVect2f.*/d' \
-e '/^"structRG_1_1Util_1_1Vect2.*/d' "$output"

fdp -Tpdf "$output" -o "$output".pdf
