﻿#pragma checksum "..\..\..\GamePage.xaml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "0CD72B2B4CC5CD1D037570894E29D98F069A8B7C"
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
    /// GamePage
    /// </summary>
    public partial class GamePage : System.Windows.Controls.Page, System.Windows.Markup.IComponentConnector {
        
        
        #line 13 "..\..\..\GamePage.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Frame backgroundPage;
        
        #line default
        #line hidden
        
        
        #line 23 "..\..\..\GamePage.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Label question;
        
        #line default
        #line hidden
        
        
        #line 35 "..\..\..\GamePage.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button Ans1;
        
        #line default
        #line hidden
        
        
        #line 36 "..\..\..\GamePage.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button Ans2;
        
        #line default
        #line hidden
        
        
        #line 37 "..\..\..\GamePage.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button Ans3;
        
        #line default
        #line hidden
        
        
        #line 38 "..\..\..\GamePage.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button Ans4;
        
        #line default
        #line hidden
        
        
        #line 51 "..\..\..\GamePage.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBlock answers;
        
        #line default
        #line hidden
        
        
        #line 52 "..\..\..\GamePage.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBlock correctAnswer;
        
        #line default
        #line hidden
        
        
        #line 56 "..\..\..\GamePage.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBlock Clock;
        
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
            System.Uri resourceLocater = new System.Uri("/trivia_client;component/gamepage.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\..\GamePage.xaml"
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
            this.question = ((System.Windows.Controls.Label)(target));
            return;
            case 3:
            this.Ans1 = ((System.Windows.Controls.Button)(target));
            
            #line 35 "..\..\..\GamePage.xaml"
            this.Ans1.Click += new System.Windows.RoutedEventHandler(this.Ans_Click);
            
            #line default
            #line hidden
            return;
            case 4:
            this.Ans2 = ((System.Windows.Controls.Button)(target));
            
            #line 36 "..\..\..\GamePage.xaml"
            this.Ans2.Click += new System.Windows.RoutedEventHandler(this.Ans_Click);
            
            #line default
            #line hidden
            return;
            case 5:
            this.Ans3 = ((System.Windows.Controls.Button)(target));
            
            #line 37 "..\..\..\GamePage.xaml"
            this.Ans3.Click += new System.Windows.RoutedEventHandler(this.Ans_Click);
            
            #line default
            #line hidden
            return;
            case 6:
            this.Ans4 = ((System.Windows.Controls.Button)(target));
            
            #line 38 "..\..\..\GamePage.xaml"
            this.Ans4.Click += new System.Windows.RoutedEventHandler(this.Ans_Click);
            
            #line default
            #line hidden
            return;
            case 7:
            this.answers = ((System.Windows.Controls.TextBlock)(target));
            return;
            case 8:
            this.correctAnswer = ((System.Windows.Controls.TextBlock)(target));
            return;
            case 9:
            this.Clock = ((System.Windows.Controls.TextBlock)(target));
            return;
            }
            this._contentLoaded = true;
        }
    }
}

