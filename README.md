# EasyJsonParser
![GALLERY0](https://user-images.githubusercontent.com/8191970/59560158-5931ed00-9048-11e9-9983-26220f3814f2.png)

## UE4 Marketplace
[https://unrealengine.com/marketplace/ja/slug/easyjsonparser](https://unrealengine.com/marketplace/ja/slug/easyjsonparser)

## Description
Usage and sample of EasyJsonParser released in the market place of UE4.



# How to use
Json string or Json file after loading, specify the access string and get the value.

![GALLERY 1](https://user-images.githubusercontent.com/8191970/59552751-a15bfb80-8fc5-11e9-8da8-767b2734a4dd.png)


# Specify Access String
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

## Get value by type

The following four functions are provided to obtain values ​​from Json:

![pic](https://user-images.githubusercontent.com/8191970/59552810-758d4580-8fc6-11e9-8a5f-09527883e26c.png)

+ ReadInt(int)
+ ReadFloat(float)
+ ReadString(string)
+ ReadBool(bool)


Enter the access string for "AccessString".

Enter the default value for "DefaultValue". If the specified value does not exist in Json, a default value is returned.

## Get object

There are also "ReadObject" and "ReadObjects" methods that get as objects instead of values.

This method can only retrieve object properties.

ReadObject gets one node object.

ReadObjects gets an array of multiple objects.

As shown below, you can use it to get an object in the middle of the hierarchy and then get the properties of that object.

![pic](https://user-images.githubusercontent.com/8191970/59552834-bb4a0e00-8fc6-11e9-8f0a-58b0ccd421d6.png)

