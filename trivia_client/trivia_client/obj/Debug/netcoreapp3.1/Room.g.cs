﻿#pragma checksum "..\..\..\Room.xaml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "8E738553F1649C79C68768B93FA14F08AB33B282"
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Controls.Ribbon;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Shell;
using trivia_client;


namespace trivia_client {
    
    
    /// <summary>
    /// RoomUsers
    /// </summary>
    public partial class RoomUsers : System.Windows.Controls.Page, System.Windows.Markup.IComponentConnector {
        
        
        #line 12 "..\..\..\Room.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Frame backgroundPage;
        
        #line default
        #line hidden
        
        
        #line 22 "..\..\..\Room.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Label header;
        
        #line default
        #line hidden
        
        
        #line 25 "..\..\..\Room.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ListView ConectedUsers;
        
        #line default
        #line hidden
        
        
        #line 40 "..\..\..\Room.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button leaveRoomButton;
        
        #line default
        #line hidden
        
        
        #line 41 "..\..\..\Room.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button closeRoomButton;
        
        #line default
        #line hidden
        
        
        #line 42 "..\..\..\Room.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button startGameButton;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "5.0.11.0")]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/trivia_client;component/room.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\..\Room.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "5.0.11.0")]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.backgroundPage = ((System.Windows.Controls.Frame)(target));
            return;
            case 2:
            this.header = ((System.Windows.Controls.Label)(target));
            return;
            case 3:
            this.ConectedUsers = ((System.Windows.Controls.ListView)(target));
            return;
            case 4:
            this.leaveRoomButton = ((System.Windows.Controls.Button)(target));
            
            #line 40 "..\..\..\Room.xaml"
            this.leaveRoomButton.Click += new System.Windows.RoutedEventHandler(this.leaveRoomButton_Click);
            
            #line default
            #line hidden
            return;
            case 5:
            this.closeRoomButton = ((System.Windows.Controls.Button)(target));
            
            #line 41 "..\..\..\Room.xaml"
            this.closeRoomButton.Click += new System.Windows.RoutedEventHandler(this.closeRoomButton_Click);
            
            #line default
            #line hidden
            return;
            case 6:
            this.startGameButton = ((System.Windows.Controls.Button)(target));
            
            #line 42 "..\..\..\Room.xaml"
            this.startGameButton.Click += new System.Windows.RoutedEventHandler(this.startGameButton_Click);
            
            #line default
            #line hidden
            return;
            }
            this._contentLoaded = true;
        }
    }
}

