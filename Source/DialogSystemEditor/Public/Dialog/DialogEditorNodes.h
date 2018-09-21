#pragma once

#include "EdGraph/EdGraphNode.h"
#include "DialogNodes.h"
#include "QaDSEdGraphNode.h"
#include "DialogEditorNodes.generated.h"

class UEdGraphPin;
class FXmlNode;

UCLASS()
class DIALOGSYSTEMEDITOR_API UDialogEdGraphNode : public UQaDSEdGraphNode
{
	GENERATED_BODY()

public:
	UEdGraphPin* InputPin;
	UEdGraphPin* OutputPin;

	UPROPERTY()
	UDialogNode* CompileNode;

	TArray<UDialogEdGraphNode*> GetChildNodes() const;
	virtual void ResetCompile() override;
	virtual int GetOrder() const;
	virtual FString SaveToXml(int tabLevel) const;
	virtual void LoadInXml(FXmlNode* xmlNode, const TMap<FString, UDialogEdGraphNode*>& nodeById);
};

UCLASS()
class DIALOGSYSTEMEDITOR_API UDialogRootEdGraphNode : public UDialogEdGraphNode
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;
	virtual FString SaveToXml(int tabLevel) const override;
	virtual bool CanUserDeleteNode() const override;
	virtual void LoadInXml(FXmlNode* xmlNode, const TMap<FString, UDialogEdGraphNode*>& nodeById) override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};

UCLASS()
class DIALOGSYSTEMEDITOR_API UDialogPhraseEdGraphNode : public UDialogEdGraphNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDialogPhraseInfo Data;

	UDialogPhraseEdGraphNode();
	virtual void AllocateDefaultPins() override;
	virtual FString SaveToXml(int tabLevel) const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void LoadInXml(FXmlNode* xmlNode, const TMap<FString, UDialogEdGraphNode*>& nodeById) override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;
};

UCLASS()
class DIALOGSYSTEMEDITOR_API UDialogPhraseEdGraphNode_Player : public UDialogPhraseEdGraphNode
{
	GENERATED_BODY()

public:
	UDialogPhraseEdGraphNode_Player();
};

UCLASS()
class DIALOGSYSTEMEDITOR_API UDialogSubGraphEdGraphNode : public UDialogEdGraphNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TAssetPtr<class UDialogAsset> TargetDialogAsset;

	virtual void AllocateDefaultPins() override;
	virtual FString SaveToXml(int tabLevel) const override;
	virtual void LoadInXml(FXmlNode* xmlNode, const TMap<FString, UDialogEdGraphNode*>& nodeById) override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};

UCLASS()
class DIALOGSYSTEMEDITOR_API UDialogElseIfEdGraphNode : public UDialogEdGraphNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDialogElseIfCondition> Conditions;

	virtual void AllocateDefaultPins() override;
	virtual FString SaveToXml(int tabLevel) const override;
	virtual void LoadInXml(FXmlNode* xmlNode, const TMap<FString, UDialogEdGraphNode*>& nodeById) override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};