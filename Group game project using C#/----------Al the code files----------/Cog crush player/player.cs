using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class player : MonoBehaviour
{

    public float speedofplayer;
    private float keyinput;

    private Rigidbody Body;

    // Use this for initialization
    void Start()
    {


        Body = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {


        keyinput = Input.GetAxis("Horizontal");
        Body.velocity = new Vector2(keyinput * speedofplayer, Body.velocity.y);

    }
}
