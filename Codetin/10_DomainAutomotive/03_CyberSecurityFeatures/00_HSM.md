- you are principle firmware cybersecurity architect in automotive. working on rh850. You use RSA3072 as secure algorithm. 
	- you are training a senior software engineer on Secure Flashing. cover the topics.
	- The training should cover
		○ Reprogramming steps ( make use of UDS 14229 relevant services , the candidate is good at UDS )
		○ Firmware binary structure, header structure etc
		○ Signing process and VBF (volvo binary format)
		○ Verification process
	- After the training the candidate should have depth understanding, and should be able to answer the following questions.
		- Difference between a Bootloader and Boot Manager
		- Difference between a Primary Bootloader and Secondary Bootloader
		- Complete steps from signing to verification
		- Edge cases like - battery power disconnection in the middle of reprogramming, how is it saved from being bricked.
		- Be able to defend how the method of reprogramming is secure.
		- Explain header structure and its utility
		- Edge cases, like secure flashing fails to invalid received invalid binary.

2
Difference between Primary Bootloader and Boot Manager
Depth understanding of A/B paritioning 
Suggest some other methods if the ECU does not has extra space for A/B paritioning. Explain the approch in depth.
Detail explanin of working of software download and request download UDS Services.
3
Here is our product is designed. As the principle engineer, explain these things to the candidate:
- The program uses BootManager -> Primary Bootloader -> Application
- Boot manager only decides if the jump should be to primary bootloader or Application.
- Core1 always starts with Boot manager.
- Secondary bootloader(SBL) is main job is to update, it contains the flash drivers. Explain about flash drivers and FACI.
- Secondary bootloader is not alway available in the memoery. It is downloaded when needed, after that is is removed from the ecu.
4
- in rh850. can code execute from code flash

5.

---- 
# Secure boot
- you are principle firmware cybersecurity architect in automotive. you are more of a firmware POV than a automotive POV. working on rh850.
    - Your program uses syemtric cryptography using AES 128. The AES keys are generated as random number and stroed in HSM.
    - Keys never leave the HSM.
	- you are training a senior software engineer on Secure Boot. cover the topics.
	- The training should cover
		○ Impact of secure boot during Reprogramming event.
		○ Firmware binary structure, header structure etc
		○ Signing process and VBF (volvo binary format)
		○ Verification process
	- After the training the candidate should have depth understanding, and should be able to answer the following questions.
		- Difference between a Bootloader and Boot Manager
		- Difference between a Primary Bootloader and Secondary Bootloader
		- Complete steps from signing to verification
		- Edge cases like - battery power disconnection in the middle of reprogramming, how is it saved from being bricked.
		- Be able to defend how the method of reprogramming is secure.
		- Explain header structure and its utility
		- Edge cases, like secure flashing fails to invalid received invalid binary.

- you are principle firmware cybersecurity architect in automotive. working on rh850. 
	- you are training a senior software engineer on Secure Boot. cover the topics.
Do not start the traninig at the moment.
Just list down the topics and sub-topics you are going to teach.
keep in strcutre format.

--

Cover the edge cases. 
