# EasyJsonParser
![GALLERY0](https://user-images.githubusercontent.com/8191970/59560158-5931ed00-9048-11e9-9983-26220f3814f2.png)

## Epic Games Fab 
[https://www.fab.com/ja/listings/0f13d0ef-a6fe-411c-8c57-9cc0f694b3f0](https://www.fab.com/ja/listings/0f13d0ef-a6fe-411c-8c57-9cc0f694b3f0)

## Description
EasyJsonParser is a powerful and user-friendly JSON parsing plugin for Unreal Engine that provides simple JSON parsing functionality with an intuitive dot-notation access pattern. The plugin supports UE 5.3 through 5.6.

### 🎉 Version 2.0 Now Available!
EasyJsonParser V2 brings significant improvements while maintaining full backward compatibility with V1. Existing users can continue using V1 and migrate to V2 at their own pace.

## What's New in V2

### 🚀 Performance Improvements
- **Lightweight Architecture**: V2 uses USTRUCT-based implementation instead of UObject, significantly reducing memory overhead and GC pressure
- **Efficient Memory Management**: Uses TSharedPtr for internal JSON storage

### ✨ New Features
- **Write Functionality**: Full JSON creation and modification support
- **Multi-dimensional Arrays**: Support for complex array structures like `matrix[0][1][2]`
- **Advanced Debug Mode**: Comprehensive logging system for troubleshooting
- **Path Auto-creation**: Automatically creates nested objects when writing to non-existent paths

### 🔧 Key Improvements
- Type-safe operations with proper error handling
- Consistent API design across all methods
- Better Blueprint integration
- File I/O operations with async support

## Choosing Between V1 and V2

### When to Use V1 (Original Version)
- Your project is already using V1 and working well
- You only need basic JSON reading functionality
- You prefer to wait before migrating to ensure stability

### When to Use V2 (New Version)
- Starting a new project
- Need JSON writing/creation capabilities
- Working with complex multi-dimensional arrays
- Want better performance and lower memory usage
- Need advanced debugging features

## Migration Guide

V1 and V2 can coexist in the same project. Here's how to migrate:

### 1. Class Name Changes
```cpp
// V1
UEasyJsonObject* JsonObject = UEasyJsonParseManager::LoadFromString(JsonString);

// V2
FEasyJsonObjectV2 JsonObject = UEasyJsonParseManagerV2::LoadFromString(JsonString);
```

### 2. Reading Values (Similar API)
```cpp
// V1
int32 Value = JsonObject->ReadInt("path.to.value", DefaultValue);

// V2 - Same syntax!
int32 Value = JsonObject.ReadInt("path.to.value", DefaultValue);
```

### 3. New Write Functionality (V2 Only)
```cpp
// Create new JSON
FEasyJsonObjectV2 NewJson = FEasyJsonObjectV2::CreateEmpty();
NewJson.WriteString("user.name", "John Doe");
NewJson.WriteInt("user.age", 30);
NewJson.WriteBool("user.active", true);

// Save to file
UEasyJsonParseManagerV2::SaveToFile(NewJson, "path/to/file.json");
```

### 4. Multi-dimensional Arrays (V2 Only)
```cpp
// Read 2D array
TArray<TArray<int32>> Matrix = JsonObject.Read2DArrayInt("data.matrix");

// Read specific element
int32 Element = JsonObject.ReadInt("data.matrix[1][2]", 0);
```

# How to use (V1 - Original Version)
Json string or Json file after loading, specify the access string and get the value.

![GALLERY 1](https://user-images.githubusercontent.com/8191970/59552751-a15bfb80-8fc5-11e9-8da8-767b2734a4dd.png)

# How to use (V2 - New Version)

## Basic Usage

### Loading JSON
```cpp
// From string
FEasyJsonObjectV2 JsonObject = UEasyJsonParseManagerV2::LoadFromString(JsonString);

// From file
FEasyJsonObjectV2 JsonObject = UEasyJsonParseManagerV2::LoadFromFile("path/to/file.json");

// Async loading
UEasyJsonAsyncLoadFromFileV2* AsyncLoader = UEasyJsonAsyncLoadFromFileV2::AsyncLoadFromFile(FilePath);
AsyncLoader->OnCompleted.AddDynamic(this, &AMyActor::OnJsonLoaded);
```

### Reading Values
```cpp
// Basic types
int32 IntValue = JsonObject.ReadInt("config.maxPlayers", 4);
float FloatValue = JsonObject.ReadFloat("player.health", 100.0f);
FString StringValue = JsonObject.ReadString("player.name", "Unknown");
bool BoolValue = JsonObject.ReadBool("settings.enableSound", true);

// Nested objects
FEasyJsonObjectV2 PlayerData = JsonObject.ReadObject("game.player");
TArray<FEasyJsonObjectV2> Items = JsonObject.ReadObjects("inventory.items");
```

### Writing Values
```cpp
// Create new JSON
FEasyJsonObjectV2 NewJson = FEasyJsonObjectV2::CreateEmpty();

// Write basic values
NewJson.WriteInt("score", 1000);
NewJson.WriteFloat("time", 45.5f);
NewJson.WriteString("playerName", "Hero");
NewJson.WriteBool("isActive", true);

// Auto-create nested paths
NewJson.WriteString("player.stats.level", "10");  // Creates player and stats objects automatically

// Arrays
NewJson.AddIntToArray("scores", 100);
NewJson.AddIntToArray("scores", 200);
NewJson.AddStringToArray("items", "Sword");
NewJson.AddStringToArray("items", "Shield");
```

### Multi-dimensional Arrays
```cpp
// Read 2D array
TArray<TArray<int32>> Matrix = JsonObject.Read2DArrayInt("gameBoard");

// Read 3D array
TArray<TArray<TArray<float>>> Voxels = JsonObject.Read3DArrayFloat("world.voxelData");

// Access specific elements
int32 Cell = JsonObject.ReadInt("gameBoard[2][3]", 0);
float Voxel = JsonObject.ReadFloat("world.voxelData[1][2][3]", 0.0f);

// Get array information
int32 ArraySize = JsonObject.GetArraySize("items");
TArray<int32> Dimensions = JsonObject.GetArrayDimensions("matrix");
```

### Saving JSON
```cpp
// To string
FString JsonString = JsonObject.ToString();

// To file
bool bSuccess = UEasyJsonParseManagerV2::SaveToFile(JsonObject, "path/to/output.json");
```

### Debug Mode
```cpp
// Enable debug logging
UEasyJsonParseManagerV2::SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel::Detailed);

// Debug specific operations
{
    EASYJSON_DEBUG_SCOPE("MyOperation");
    FEasyJsonObjectV2 Data = JsonObject.ReadObject("complex.data");
    // Debug info will be logged automatically
}

// Disable debug logging
UEasyJsonParseManagerV2::SetDebugLogLevel(EEasyJsonParserV2DebugLogLevel::None);
```

## Blueprint Usage

All V2 functionality is available in Blueprints through the EasyJsonParserV2 category.

### Example Blueprint Nodes
- **Load From String V2** - Load JSON from string
- **Load From File V2** - Load JSON from file
- **Save To File V2** - Save JSON to file
- **Read Int V2** - Read integer value
- **Write String V2** - Write string value
- **Create Empty V2** - Create new JSON object
- **Add to Array V2** - Add values to arrays

# Specify Access String (Common to V1 and V2)
Specify the path to the value you want to get by connecting dots.

## Simple case
The access string for taking a "prop" value from the following simple Json is `prop`.

```json
{
  "prop":"abc"
}
```


## When it is a hierarchy of objects
If you have a hierarchy as shown below, connect with dots to create an access string.

In the following case, the access string is `obj.prop` because we want to take the` prop` property in the object `obj`.

```json
{
  "obj":
  {
    "prop":"abc"
  }
}
```

## If the array is included
In the case of the following array, please specify which array element to use.

For example, if you want to take the second `prop`, it will be `obj[1].prop`.

If you want to take the first `prop`, it will be`obj[0].prop`.

```json
{
  "obj":[
  {
    "prop":"abc"
  },
  {
    "prop":"def"
  }
  ]
}
```

## Multi-dimensional Arrays (V2 Only)
V2 supports accessing multi-dimensional arrays:

```json
{
  "matrix": [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
  ]
}
```

Access patterns:
- `matrix[0][0]` → 1
- `matrix[1][2]` → 6
- `matrix[2][1]` → 8

## Get value by type (V1)

The following four functions are provided to obtain values ​​from Json:

![pic](https://user-images.githubusercontent.com/8191970/59552810-758d4580-8fc6-11e9-8a5f-09527883e26c.png)

+ ReadInt(int)
+ ReadFloat(float)
+ ReadString(string)
+ ReadBool(bool)


Enter the access string for "AccessString".

Enter the default value for "DefaultValue". If the specified value does not exist in Json, a default value is returned.

## Get object (V1)

There are also "ReadObject" and "ReadObjects" methods that get as objects instead of values.

This method can only retrieve object properties.

ReadObject gets one node object.

ReadObjects gets an array of multiple objects.

As shown below, you can use it to get an object in the middle of the hierarchy and then get the properties of that object.

![pic](https://user-images.githubusercontent.com/8191970/59552834-bb4a0e00-8fc6-11e9-8f0a-58b0ccd421d6.png)

## Performance Comparison

| Feature | V1 | V2 |
|---------|----|----|
| Memory Usage | Higher (UObject-based) | Lower (USTRUCT-based) |
| GC Pressure | Higher | Minimal |
| JSON Writing | ❌ | ✅ |
| Multi-dimensional Arrays | Limited | Full Support |
| Debug Mode | Basic | Advanced |
| Blueprint Support | Full | Full |

## Support

For questions, issues, or feature requests, please visit our [GitHub repository](https://github.com/ayumax/EasyJsonParser).
