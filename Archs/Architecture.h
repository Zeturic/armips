#pragma once

#include "Commands/CAssemblerCommand.h"
#include "Util/ByteArray.h"

#include <map>
#include <memory>

class IElfRelocator;
class Tokenizer;
class Parser;

struct ExpressionFunctionEntry;

using ExpressionFunctionMap =  std::map<std::wstring, const ExpressionFunctionEntry>;

class Architecture
{
public:
	static Architecture &current();
	static void setCurrent(Architecture &arch);

	virtual std::unique_ptr<CAssemblerCommand> parseDirective(Parser& parser) { return nullptr; }
	virtual std::unique_ptr<CAssemblerCommand> parseOpcode(Parser& parser) { return nullptr; }
	virtual const ExpressionFunctionMap& getExpressionFunctions();
	virtual void NextSection() = 0;
	virtual void Pass2() = 0;
	virtual void Revalidate() = 0;
	virtual std::unique_ptr<IElfRelocator> getElfRelocator() = 0;
	virtual Endianness getEndianness() = 0;
private:
	static Architecture *currentArchitecture;
};

class ArchitectureCommand: public CAssemblerCommand
{
public:
	ArchitectureCommand(const std::wstring& tempText, const std::wstring& symText);
	bool Validate(const ValidateState &state) override;
	void Encode() const override;
	void writeTempData(TempData& tempData) const override;
	void writeSymData(SymbolData& symData) const override;
private:
	Architecture *architecture = nullptr;
	int64_t position;
	Endianness endianness;
	std::wstring tempText;
	std::wstring symText;
};

class CInvalidArchitecture: public Architecture
{
public:
	void NextSection() override;
	void Pass2() override;
	void Revalidate() override;
	std::unique_ptr<IElfRelocator> getElfRelocator() override;
	Endianness getEndianness() override { return Endianness::Little; }
};

extern CInvalidArchitecture InvalidArchitecture;
