# Building Escape Tech Demo - Dev Journal

###### _Developed with Unreal Engine 4_

_My place to keep my journal entries that I have written along the way while learning **Unreal Engine 4**.
Code Snippets, Links, References, and Personal Notes/Reminders._

## Resources:
[Unreal Course](https://www.udemy.com/share/101WeuB0AYc1hXQH4=/) - Unreal Engine C++ Developer: Learn C++ and Make Video Games _(Udemy)_.

[Unreal Engine 4 Documentation](https://docs.unrealengine.com/en-US/index.html) - Official Unreal Engine 4 Docs.

[Git for UE4 / Unreal Engine 4](https://www.youtube.com/watch?v=FXMTHrLWFKQ&ab_channel=DevEnabled) - YouTube video tutorial on utilizing Git & Git LFS for use in UE4 Projects.

[Textures.com](https://www.textures.com/library) - Website for downloaded high quality texture assets.

[Binary Space Partitioning](https://www.geeksforgeeks.org/binary-space-partitioning/) - A GeeksForGeeks article explaining Binary Space Partitioning _(UE4 BSP Geometry)_.

## Learning Unreal Engine 4 - Developer Log

I have finished setting up git LFS for this project. Any potential people in the future that would want to clone this repo would need to have installed git LFS on their end in order to do so successfully. Building Escape is a go!

I will be using the [Unreal Course Tutorial](https://www.udemy.com/share/101WeuB0AYc1hXQH4=/) to use as my main learning tool to build this tech demo. Throughout the tutorial lectures, there are many points in which I will want to be able to discuss and share my solutions and compare them to other's submissions: [GameDev.tv Community](https://community.gamedev.tv/)

### **2021-04-22** -- _Pointers_
- Denoted by when you see/use `*` next to a type.
- Pointers are memory addresses.
- Similar to references, using pointers allows us to save moving/copying things by reference.
- Can post to most objects.
- If one is not careful there may be times where one can lose control/track of data.

Template: `FType* NameOfPointer;`

Where: `NameOfPointer` is the pointer, and 
type of object pointed to is `FType`.

Use Case Example: 
- `AActor* SomeActor;`
`AActor` class has method `GetName()`
`*SomeActor` "dereferences" the pointer.

  - We could then write: `(*SomeActor).GetName();`
  - Instead we could use SomeActor->GetName(); to follow and utilize the same method through the pointer.
  - Essentially `(*SomeActor).GetName();` is equal to `SomeActor->GetName();`

- Use `->` with pointers, and `.` for regular variables.

### -- _Inheritance_

Today I am creating a new Actor component (WorldPosition) so that I can attach this component to any of the actors within the level to instantly find their Location Transform values.

Some things that I have learned throughout the video lectures as well as through self exploration:
- Class Viewer; Unreal's class system:
> Window -> Developer Tools -> Class Viewer
- Character = Pawn = Actor _(Dog is Mammal, Mammal is Animal)_
- Because of Inheritance, components will share base behaviour/features from their parent class.
- Some are necessary, i.e. mesh, collision, audio can only be components.
- Actors can have custom user-made components.

**To Delete Components:**
1. Make sure it is not a component for any other actors. 
1. Delete from file explorer. 
1. Delete binaries.

### -- _Logging in UE4_
Learning today how to set my own feedback messages at run-time within Unreal so I am able debug within the future.

- Format:  `UE_LOG(Category, Verbosity, TEXT("Message"));`
  - Example: `UE_LOG(LogTemp, Warning, TEXT("Hello"));`
>**Verbosity** is the colour that the log outputs to the user: 
> - Error = Red | Warning = Yellow | Display = Grey

### -- _Configuring Default Startup Level_
- Default Startup Level:
>Project Settings -> Maps & Modes -> Default Maps -> Editor Startup Map -> (Choose Level).

### -- _Continuing with Pointers_
- Pointers: `&` indicates a reference, however, it points to the variables memory address.
- We can use `*` to dereference a pointer.
- `.` operator takes precedence over dereferenceing. 
  - This is why we need brackets first -
  - Example: `*Ptr.Len()` does not work, but `(*Ptr).Len()` does.
- `.` gives direct access to members, whereas `->` gives indirect access through pointers.
- Need to use `**` in order to dereference pointer, as well as effectively converting the string to type `TCHAR array`.


### **2021-04-23** -- _TEXT Macro_
The `TEXT` macro is to ensure the correct data type for a character or string literal. That being
```
'a'
"string"
```
respectively.

- Unreal’s native encoding is Unicode and different platforms handle that differently. For example Windows natively supports Unicode and uses the `wchar_t` type to store Unicode code points.

- So instead of
`'a'`
Windows would need
`L'a';`
The L prefix makes the type of the literal `wchar_t` instead of `char`.

As other platforms require different character types to handle Unicode, Unreal provides `TCHAR` type alias and the `TEXT` macro so that the right type and literal is used for the targeted platform. On Windows `TCHAR` would be wchar_t and the `TEXT` macro prepends an **L**.

### -- _Getting Location for Custom **World Position** Component_

I have been getting more exposure to the Unreal Documentation, and have been able to use it quite efficiently.

We are working with FVectors and FTransforms as the main unit types for this component.

- My inital way to find our location: ```GetOwner()->GetActorTransform().GetLocation().ToString();```
- The more efficient way I refactored to later on: ```GetOwner()->GetActorLocation().ToString();```

### -- _Working with FBX Importing_
We need something in our scene to move.

Import using Content Browser -> Finished imported my own textures from [Textures.com](https://www.textures.com/library)

- When dealing with materials, it has been suggested as best practice to create an instance of said material rather than working directly from the base material.

- Able to press F2 to rename assets, and should be able to right-click + fix up references incase there are any re-naming conflicts.

### -- _Binary Space Partitioning_
Using Binary Space Partitioning (BSP) geometry, we are utilize and customize 3D objects to use for level design purposes.
- Good for quickly mocking up an idea or level design.
- There are various brushes that can be used.
- The order matters on how you use these in terms.

> Do not rely on BSPs for the final game product:
> - Bad Performance.
> - Should only be used for level design drafts/mockups.

For now I am able to create a quick mockup level here using BSPs to create a simple 'square' room with a roof.

Created and organized different box brushes to use as test-level walls to get used to laying out a mockup level.

Rebuilding tends to fix many of the issues for the most part.

In terms of collision, and other _janky_ effects from the BSPs, converting these into Static Mesh's should fix this.
- However, the model quality will suffer as it is derrived from a BSP.
  - The safest bet for model quality would be to create it from scratch within proper tools such as Blender.

![Aerial Look on the Room](https://user-images.githubusercontent.com/59905099/118882383-c2b47900-b8b9-11eb-9d60-88b9a255b363.png)

### **2021-04-24** -- _Lighting_

Dragged in some lighting effects within the the level mockup to provide the player vision, as well as, provide a sense of where the objectives lie.

Used a few spotlights as simple torches to illuminate the room, as well as a point light in the corner as a main light source.

### -- _Scaling Textures_

Today I have created a texture coordinator node, as well as a scaling parameter node.

I have joined both of these two nodes together within a multiply node.

- **U** and **V** = **X** and **Y** cooordinates of the texture image.

Created a second texture scale in and joined together using an append node.

- This allows us to independently control both the **U** and **V** coordinates for our Texture/Material Instance!

### -- _Creating Custom OpenDoor Actor Component_

Initialized and created through UE4 an Actor Component named **`OpenDoor`**.

Like the name suggest, I will be using this component to add to the existing door assets so we can control when our Door Opens/Closes.

### -- _Creating Floats_
Creating `floats` -> implicitly converts `ints` and `doubles`

- To set a float: add **f** to the end. 
 - Ex: `float MyFloat = 90.f;` // We can add the 0 at the end or not, Unreal Docs don't.
- Rotation values (can hover over in UE4): `X = Roll`, `Y = Pitch`, `Z = Yaw` 
- `FRotator` is constructed in order: **YZX**

_We don't currently have an owner, typically bad to put GetOwner() in BeginPlay()._

### -- _Working with Object Collision_

I am going to be looking through this tutorial about looking at object collision with UE4. At first I was having an issue with my actor being unable to move throughout certain points in the level, and mainly the door. It turns out the the asset for the tutorial's door frame went through the door, so I had to go into the asset editor and manually remove collision points. Whilst throughout learning in the tutorial video they gave good points about other possibile solutions:

- 4 Options:
 - Remove Collider
 - Convert to Complex Collision (expensive & bad practice)
 - Convert BSP to Static Mesh
 - Get an Artist to provide Assets with collision
 
_Should avoid using complex collision as simple._ 
So, we simply removed the collision and we can now phase through.

Materials are Shader(s) plus texture(s) that determine how a mesh's surface is rendered.

### **2021-04-25** -- _Linear Interpolation (Lerp)_

`FMath::Lerp(Start, End, %Distance)`

We are working now with interpolations in order to make our door in our mock level swing open. We are using the Yaw value in the objects rotation in order to create the door-opening effect/functionality.

I have been learning the difference between different number different inputs when trying to interpolate. I struggled initially with trying to find the correct way to use to get the type of door swing that I wanted.

When using within the tick component, when we use the `Lerp` function, the percentage becomes exponential interpolation rather than linear.

After digging through the docs for a while, I found that actual Linear Interpolation would need to use:

`FMath::FInterpConstantTo(float Current, float Target, float DeltaTime, float InterpSpeed(//which is degrees per second));`

--> This results in the door swinging open at a constant rate.

Another function which we can use to get the door to swing open:

`FInterpTo (float CurrentValue, float TargetValue, float DeltaTime, float InterpSpeed)`

--> This will make quickly open and then smooth out.

### -- _Working with Derrived Blueprints_
`UPROPERTY(EditAnywhere)` - This allows you to access this and set per each actor.

Knowing we are able to create Blueprint properties from C++, I can tell this will be useful information to know.

I did some additional research on the permissions/identifiers for Blueprint properties. I am going to keep this table here as a reference.

**Looking at Access Modifiers for different `UPROPERTY(//Values)`:**

Value | Affects | Access
--- | --- | ---
`VisibleAnywhere` | Defaults & Instances |Read Only*
`VisibleDefaultsOnly` | Defaults | Read Only
`EditAnywhere` | Defaults & Instances | Read/Write**
`EditDefaultsOnly` | Defaults | Read/Write
`VisibleInstanceOnly` | Instances | Read Only
`EditInstanceOnly` | Instances | Read/Write
`BlueprintReadOnly` | Blueprints | Read Only
`BlueprintReadWrite` | Blueprints | Read/Write


***ReadOnly** -> Get

****ReadWrite** -> Get/Set


Example: `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"));`

- The _`Category`_ is what you can see in the editor window.
- The _`meta`_ = `(AllowPrivateAccess = "true")` is how I am able to make private C++ classes visible within the editor, while still keeping them private. Keeping a mental note of this.

### **2021-04-26** -- _Trigger Volumes_
Trigger Volumes:

Creating a Trigger Volume and utilizing it as a set point of contact/interest for future events within the game. 
I am creating mine in order to transpire the effect of the doors opening whenever there is an object placed within.

The end goal for our door is to have an object with a heavy enough mass to enter the Trigger Volume, and then trigger our Door to open.

![Showing the TriggerVolume and Lighting](https://user-images.githubusercontent.com/59905099/118882495-de1f8400-b8b9-11eb-845a-9c5687b30fad.png)

### -- _DeltaTime_

DeltaTime used so that speed of objects isn't determined by individual PC performance

> Side note, I I have just found out recently how to eject from the Character/Actor/Pawn that we are possessing:
> 
> `(F8, or Shift + F1 and Eject).`
>
> 
> This allows me to better manouvre and see our default actor's mass in the World Outliner and start debugging the Trigger Volume.
>

DeltaTime is used to acquire the elapsed time between frames.

### -- _Opening Door(s)_

Finished refactoring the opening of the door into its own separate function:

```
  void UOpenDoor::OpenDoor(float DeltaTime)
  {
    CurrentRotation = GetOwner()->GetActorRotation();
    CurrentYaw = CurrentRotation.Yaw;
    NewRotation.Yaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, DoorOpenSpeed);
    GetOwner()->SetActorRotation(NewRotation);

    bCloseDoorSoundPlayed = false;
    if(!AudioComponent){return;}
    if(!bOpenDoorSoundPlayed)
    {
      AudioComponent->Play();
      bOpenDoorSoundPlayed = true;
    }
  }
```

We now have an if statement within our `TickComponent()`function that runs `OpenDoor` if we step on the **PressurePlate**:

```
  // Called every frame
  void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
  {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if(TotalMassOfActors() >= MassToOpenDoors)
    {
      OpenDoor(DeltaTime);
      DoorLastOpened = GetWorld()->GetTimeSeconds(); // Door timer.
    }
    else
    {
      if (GetWorld()->GetTimeSeconds() >= DoorLastOpened + DoorCloseDelay)
      {
        CloseDoor(DeltaTime);
      }
    }
  }
```

### **2021-04-27** -- _Coding for Null Pointer Protection_

I firstly created a few Log messages for Null Pointer Protection.

I then added these Logs to `PressurePlate` as well as to the `if` condition.

- This way it will only execute if `PressurePlate` has a value.
- I have coded so that there will be output to the Logs with an error/warning message stating whether or not there are any `OpenDoor` components without a `PressurePlate` Trigger Volume.

Learning more about the hierarchy of Unreal components, as I have needed to gain access to the World Engine, and GameFramework for access to the PlayerController.

`GetWorld()->GetFirstPlayerController()` accesses the first player controller (singleplayer game).
> Personal note - Pawns are a subset of Actors.


### -- _Closing Door(s)_
Created a `CloseDoor()` function similar to `OpenDoor()` so that when off of the trigger colume, the door will automatically **revert** to previous position.

```
  void UOpenDoor::CloseDoor(float DeltaTime)
  {
    CurrentRotation = GetOwner()->GetActorRotation();
    CurrentYaw = CurrentRotation.Yaw;
    NewRotation.Yaw = FMath::FInterpConstantTo(CurrentYaw, InitialYaw, DeltaTime, DoorCloseSpeed);
    GetOwner()->SetActorRotation(NewRotation);

    bOpenDoorSoundPlayed = false;
    if(!AudioComponent){return;}
    if(!bCloseDoorSoundPlayed)
    {
      AudioComponent->Play();
      bCloseDoorSoundPlayed = true;
    }
  }
```

### **2021-04-28** -- _Updated Open/Close Door Functions_
Using `GetWorld()->GetTimeSeconds()` above, I have created an `If/Else` with the World Time in Seconds related to the `DoorLastOpened` and `DoorCloseDelay` member variables that I created. I have updated the above code to show this.

###-- _Game Modes_

GameModes are within UE4 to set how a game should function.

- GameModes can include/deal with the following:
 - Time Limits
 - Amount of Lives
 - Score needed to end the game

All of this and more belong to GameMode.

###-- _Continuing with Blueprints_

I have found that Blueprints are helpful in creating templates for assets. I have made a new Blueprint to inherit the GameMode we have created.

**DefaultPawn_BP** is an asset, and we want to be able to track changes to its name (why we use blueprint instead of C++). We are able to extend the  C++ GameMode with Blueprints.

### -- _Getting Players Viewpoint_
I am now finding out how to find the player's viewpoint so that they are able to Ray-cast out to a certain distance (this will essentially act as our character's reach).

Getting the Player's ViewPoint Location:
```
  FVector PlayerViewPointLocation = GetOwner()->GetActorLocation();
  FRotator PlayerViewPointRotation = GetOwner()->GetActorRotation();

  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

  return PlayerViewPointLocation;
```
If we want the Player's Reach:
```
  return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
```

- `PlayerViewPointRotation.Vector()` converts to a Unit Vector.
- Created private float `Reach` to be `125.f;`
- `Reach` is a member variable that we have set in the Grabber header file.
 - We multiply `PlayerViewPointRotation.Vector()` by the `Reach` so as get our end position to RayCast to the object we are looking to pick up without accidentally hitting ourselves (a.k.a. the Actor we inhabit).
 - This is due to the fact that the Unit Vector from `PlayerViewPointRotation.Vector()` returns a value of **1**.

Since we are using some functions which utilize different _Out-Parameters_, I created a macro `#define`**`OUT`** to prefix to them as a tag for my own readability.

### -- _Drawing a Debug Line for our RayTracing_

I have used [`DrawDebugLine()`](https://docs.unrealengine.com/en-US/API/Runtime/Engine/DrawDebugLine/index.html) in order to visualise the vector for our player's reach for debugging and testing purposes (I will delete later).
- RayCasting is also known as Line Tracing.
 - Debug Line **!=** RayCast

### -- _Continuing with Line Tracing (RayTrace)_
- I have been using nullptr to initialise pointers for further safety, and have logged errors to check if our `PhysicsHandle` Component is attached or not. 
- Added our PhysicsHandle Component to the DefaultPawn_BP.

Checking for the Physics Handle Component:
`GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();`

```
  FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
  {
    FHitResult Hit;
    FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

    // Ray-cast out to a certain distance (Reach):
    GetWorld()->LineTraceSingleByObjectType(OUT Hit, GetPlayerWorldPosition(), GetPlayerReach(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);

    return Hit;
  }
```
Going to Line Trace using [LineTraceSingleByObjectType()](https://docs.unrealengine.com/en-US/API/Runtime/Engine/Engine/UWorld/LineTraceSingleByObjectType/index.html): `GetWorld()->LineTraceSingleByObjectType`. We can then use `ECollisionChannel` (uses :: to access things as it is an enum) as the `FCollisionObjectQueryParams` parameter and select `ECC_PhysicsBody`.

This `bool` will return successful if an object with `PhysicsBody` collision is hit with the LineTrace.

### **2021-04-29** -- _Input Binding_

> **Project Settings -> Engine -> Input -> Bindings**

I was unable to correctly log that the input bindings were set, so I did some digging and found a solution which I used to additionally set both the Auto Possess Player and Auto Receive Input both to _'Player 0'_ instead of _'Disabled'_ ([GameDev.tv Forum Solution](https://community.gamedev.tv/t/cant-find-inputcomponent-ue4-16-3/38521/5?u=sauce)).

> Personal Notes on Accessors & Memory Layout:
>
>- Use **`::`** (scope operator) to access (class, enum, namespace) in permanent storage
>- Use **`->`** to acess pointers (free store/heap)
>- Use **`.`** to access instance or reference (stack)
> >- Intellisense -> if it's purple cube; that's a function.

### -- _Refactoring TickComponent Function, and Rest of Codebase_
A _"hot loop"_ is code that gets called often - ex: `TickComponent`! Thus, I felt it necessary to  create separate `Grab()` and `Release()` methods so that it's not used **PER TICK** for better refactoring.

I am taking my time to go through my code and remove unessescary lines of code in which I can move over to its own separate function.

Current Guidelines to Refactoring I am using:

>**-R-G-R- method**:
>
>**-Red-** 
> - Code is not working (test failing).
>
>**-Green-** 
> - Code is working (ugly is OK).
>
>**-Refactor-**
> - Make it pretty (must still work)!

- Reduce current code to fewer lines that are **still clear!** (**Clear** is Key)
- Taking time to name things appropriately
- Comments should be used throughout to explain _'why'_ we are doing things in a certain way.
 - The _'what'_ of what a section is doing should be obvious.

### -- _Including `Components/PrimiticComponent` to `OpenDoor.cpp`_
Went through and included `Components/PrimitiveComponent` to the `OpenDoor.cpp`.
This allowed me to then work on changing the initial `TriggerVolume` to open when
the set mass (able to now be edited in UE) surpasses a certain value based on the objects placed inside (which also have their own set mass).

I ran across a probelm in which the objects were not triggering inside the volume until I realized that the `Generate Overlap Events` tickbox was unticked. After enabling this setting, everything ran smoothly as expected.

### **2021-04-30** -- _Adding SFX and Audio Clips_

Added an audio component to door objects, which once created, allows me to either drag and drop, or select files from the drop down menu in the **Sound** section of the details pane.
Successfully imported `door-lock.wav` file to use for the door-opening sound.
once created, either drag and drop or select from drop down menu in the Sound section of the details pane.

- According to UE docs, anything with U proceeding it should have UPROPERTY() before it.
 - Otherwise, that macro will not be able to tidy/clean things up for us.

With the audio components created and set, it is time to implmenet some Boolean Logic to activate them.

Finding our Audio Component:
```
  void UOpenDoor::FindAudioComponent()
  {
    AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

    if (!AudioComponent)
    {
      UE_LOG(LogTemp, Error, TEXT("%s - Missing Audio Component!"), *GetOwner()->GetName());
    }
  }
```

**OpenDoor()** Sound Functionality:
```
  bCloseDoorSoundPlayed = false;
  if(!AudioComponent){return;}
  if(!bOpenDoorSoundPlayed)
  {
    AudioComponent->Play();
    bOpenDoorSoundPlayed = true;
  }
```
**CloseDoor()** Sound Functionality:
```
  bOpenDoorSoundPlayed = false;
  if(!AudioComponent){return;}
  if(!bCloseDoorSoundPlayed)
  {
    AudioComponent->Play();
    bCloseDoorSoundPlayed = true;
  }
```

### **2021-05-1** -- _Finalizing BuildingEscape Tech Demo/Mockup_

In terms of the overall project completion, we now have the basic building blocks of what could be flushed out into being a functional Technical Demo for a future Level Designer/Artist. They can now easily come in and create an Indian Jones type of temple escape -- or whatever they fancy!

Linked Below to the YouTube Play button is a Quick Demo of the project so far:

[![Quick Demo: Building Escape - (Unreal Engine 4 Dev Log)](https://user-images.githubusercontent.com/59905099/119030415-788dcf00-b96f-11eb-9427-f1842568e4cb.jpg)
](https://www.youtube.com/watch?v=WfLD5G_lm54&ab_channel=GarretBrowning)

![Inside of the Room](https://user-images.githubusercontent.com/59905099/118882515-e4adfb80-b8b9-11eb-8984-ef8e78c02a05.png)

For future plans and implementation, I have finished downloading and adding a free asset pack from the Unreal Store. The pack I chose was Medieval Dungeon, and I plan on working further to create my own level variant which I can finish on later on for a cleaner look compared to the current BSP demo.
